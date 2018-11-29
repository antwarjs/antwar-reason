open Common;

module Make = (Component: {type t;}, Fs: Filesystem.T) => {
  type component = Component.t;
  type compileUnit = (url_path, component);
  type transform = (~index: int, compileUnit) => compileUnit;

  type t = {
    buildDir: string,
    mapUrlToFile: url_path => string,
    processComponent: component => string /* maybe Html_string.t? */
  };

  let defaultMapUrlToFile = Util.concatUrlPath;

  let defaultProcessComponent = (_component: component) => "";

  let make =
      (
        ~buildDir,
        ~mapUrlToFile=defaultMapUrlToFile,
        ~processComponent=defaultProcessComponent,
        (),
      ) => {
    buildDir,
    mapUrlToFile,
    processComponent,
  };

  let setup = ({buildDir}: t): unit => Fs.mkdirp(buildDir);

  let compilePage = (compiler: t, compileUnit: compileUnit): unit => {
    let {processComponent} = compiler;
    let (path, component) = compileUnit;

    processComponent(component) |> Fs.writeFile(~filepath="");
  };

  let compileAll = (compiler: t, input: array(compileUnit)): unit => {
    setup(compiler);

    let compile = compilePage(compiler);
    Array.iter(compile, input);
  };
};
