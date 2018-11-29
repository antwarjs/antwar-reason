module Make = (Component: {type t;}, Fs: Filesystem.T) => {
  type url_path = UrlPath.t;
  type component = Component.t;
  type compileUnit = (url_path, component);
  type transform = (~index: int, compileUnit) => compileUnit;

  type t = {
    buildDir: string,
    mapUrlToFile: url_path => string,
    processComponent: component => string /* maybe Html_string.t? */
  };

  /*
      [] => "index.html"
      ["about"] => "about/index.html"
      ["about", "2"] => "about/2/index.html"
   */
  let defaultMapUrlToFile = urlPath =>
    Path.(join([join(urlPath)] @ ["index.html"]));

  let make =
      (
        ~buildDir,
        ~mapUrlToFile=defaultMapUrlToFile,
        ~processComponent=_ => "",
        (),
      ) => {
    buildDir,
    mapUrlToFile,
    processComponent,
  };

  let setup = ({buildDir}: t): unit => Fs.mkdirp(buildDir);

  let compilePage = (compiler: t, compileUnit: compileUnit): unit => {
    let {buildDir, processComponent, mapUrlToFile} = compiler;
    let (urlPath, component) = compileUnit;

    let filepath = Path.(join([buildDir, mapUrlToFile(urlPath)]));

    let content = processComponent(component);

    Fs.mkdirp(Path.dirname(filepath));
    Fs.writeFile(~filepath, content);
  };

  let compileAll = (compiler: t, input: array(compileUnit)): unit => {
    setup(compiler);

    let compile = compilePage(compiler);
    Array.iter(compile, input);
  };
};
