module type T = {
  let writeFile: (~filepath: string, string) => unit;
  let touchFile: string => unit;
  let mkdirp: string => unit;
};

module Console: T = {
  let writeFile = (~filepath: string, content): unit => {
    Js.log("Writing to file: " ++ filepath);
    Js.log(content);
  };
  let touchFile = filepath: unit => ();
  let mkdirp = dirpath => Js.log("mkdirp: " ++ dirpath);
};

module Node: T = {
  include Console;
};
