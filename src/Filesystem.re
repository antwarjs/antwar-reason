module type T = {
  let exists: string => bool;
  let writeFile: (~filepath: string, string) => unit;
  let touchFile: string => unit;
  let mkdir: string => unit;
  let mkdirp: string => unit;
};

module Console: T = {
  let exists = path => {
    Js.log("exists: " ++ path);
    false;
  };
  let writeFile = (~filepath: string, content): unit => {
    Js.log("Writing to file: " ++ filepath);
    Js.log(content);
  };
  let touchFile = filepath: unit => ();
  let mkdir = dirpath => Js.log("mkdir: " ++ dirpath);
  let mkdirp = dirpath => Js.log("mkdirp: " ++ dirpath);
};

module Node: T = {
  [@bs.module "fs"] external mkdirSync: string => unit = "";
  [@bs.module "fs"] external existsSync: string => bool = "";
  [@bs.module "fs"]
  external openSyncR:
    (string, [@bs.string] [ | [@bs.as "r+"] `ReadWrite]) => int =
    "openSync";

  [@bs.module "fs"] external closeSync: int => unit = "";

  /* Doesn't seem to bump the access time yet */
  let touchFile = filepath => openSyncR(filepath, `ReadWrite) |> closeSync;

  let exists = path => existsSync(path);

  let mkdir = dirpath =>
    if (exists(dirpath)) {
      ();
    } else {
      try (mkdirSync(dirpath)) {
      | Js.Exn.Error(e) =>
        switch (Js.Exn.message(e)) {
        | _ => ()
        }
      };
    };

  /*
     Input: "/Projects/Users/project/build/about"

     Steps:
     1) Strip cwd & file: "build/about"
     2) Calc paths & add cwd back: ["$cwd/build", "$cwd/build/about"]
     3) Execute mkdir on each dirpath
   */
  let mkdirp = dirpath => {
    open Path;
    let splits = withoutCwd(dirpath) |> Js.String.split(Path.sep);

    Array.fold_left(
      (base, next) => {
        let path = join([base, next]);
        mkdir(path);
        path;
      },
      cwd,
      splits,
    );

    ();
  };

  let writeFile = (~filepath: string, content) =>
    Node.Fs.writeFileAsUtf8Sync(filepath, content);
};
