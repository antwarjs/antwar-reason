module Make = (Component: {type t;}, Fs: Filesystem.T) => {
  module CompileUnit = CompileUnit.Make(Component);

  module BundleResult = {
    type result =
      | Ok
      | Error(string);

    type t = {
      bundle: CompileUnit.bundle,
      outputFile: string,
      result,
    };

    let compare = (r1, r2) => Pervasives.compare(r1.bundle.id, r2.bundle.id);
  };

  module BundleResultSet = Set.Make(BundleResult);

  type url_path = UrlPath.t;
  type component = Component.t;

  type transform = (~index: int, CompileUnit.t) => CompileUnit.t;

  type t = {
    buildDir: string,
    bundleDir: string,
  };

  /*
      [] => "index.html"
      ["about"] => "about/index.html"
      ["about", "2"] => "about/2/index.html"
   */
  let mapUrlToFile = (urlPath: UrlPath.t) =>
    Path.(join([join(urlPath)] @ ["index.html"]));

  let processComponent = (comp: Component.t) => "";

  let make =
      (
        ~buildDir=Path.join([Sys.getcwd(), "build"]),
        ~bundleDir=Path.join([Sys.getcwd(), "bundle"]),
        (),
      ) => {
    buildDir,
    bundleDir,
  };

  let setup = ({buildDir}: t): unit => Fs.mkdirp(buildDir);

  let compilePage = (compiler: t, page: CompileUnit.page): unit => {
    let {buildDir} = compiler;
    let {CompileUnit.urlPath, component} = page;

    let filepath = Path.(join([buildDir, mapUrlToFile(urlPath)]));

    let content = processComponent(component);

    Fs.mkdirp(Path.dirname(filepath));
    Fs.writeFile(~filepath, content);
  };

  let compileBundle =
      (compiler: t, bundle: CompileUnit.bundle): Js.Promise.t(BundleResult.t) => {
    let {buildDir, bundleDir} = compiler;
    let {CompileUnit.id, entry} = bundle;

    /*
        For fastpack, we need to create a directory per bundle, since it's not
        capable to output a different filename than `index.js`
        See: https://github.com/fastpack/fastpack/issues/145
     */
    let outputDir = Path.join([bundleDir, id]);
    let outputFile = Path.join([outputDir, "index.js"]);

    Bundler.Fastpack.(
      make(
        ~entry="./site/app.bs.js",
        ~task=Build,
        ~dev=true,
        ~output=outputDir,
        ~preprocess=[
          "\\.css$:style-loader!css-loader?importLoaders=1!postcss-loader?path=./postcss.config.js",
        ],
        (),
      )
      |> exec
      |> Js.Promise.then_(code =>
           (
             switch (code) {
             | 0 => {BundleResult.bundle, outputFile, result: Ok}
             | _ => {
                 BundleResult.bundle,
                 outputFile,
                 result: Error("Building bundle '" ++ id ++ "' failed"),
               }
             }
           )
           |> Js.Promise.resolve
         )
    );
  };

  let compileAll =
      (compiler: t, input: list(CompileUnit.t)): Js.Promise.t(unit) => {
    setup(compiler);

    /* Steps to do
          - Categorize all compileUnits to bundles / static pages
          - Run fastpack for each bundle, wait until all bundles are built
          - Remember all succcessfully built bundles, so we can use them in the pages
          - Render all Static pages, check for bundle deps and insert the
            code for mounting the bundle

       */

    let bundles =
      List.fold_left(
        (ret, next) =>
          switch (next) {
          | CompileUnit.Bundle(bundle) => [bundle, ...ret]
          | _ => ret
          },
        [],
        input,
      );

    List.map(bundle => compileBundle(compiler, bundle), bundles)
    |> Array.of_list
    |> Js.Promise.all
    |> Js.Promise.then_(results =>
         Array.to_list(results)
         |> BundleResultSet.of_list
         |> Js.Promise.resolve
       )
    |> Js.Promise.then_(bundleResults => {
         Js.log("Bundle Builds:\n--------------------");
         BundleResultSet.iter(
           bundleResult => {
             open CompileUnit;
             open BundleResult;

             let {id} = bundleResult.bundle;
             let {outputFile} = bundleResult;

             let result =
               switch (bundleResult.result) {
               | Ok => "OK"
               | Error(_) => "FAILED"
               };

             Js.log({j|$id \t - $outputFile \t [$result]|j});
           },
           bundleResults,
         );

         Js.Promise.resolve();
       });
    /*let compile = compilePage(compiler);*/
    /*Array.iter(compile, input);*/
  };
};
