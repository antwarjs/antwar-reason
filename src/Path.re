let cwd = Sys.getcwd();
let sep = Filename.dir_sep;

let withoutCwd = (filepath: string): string =>
  Js.String.(
    if (startsWith(cwd, filepath)) {
      switch (split(cwd ++ sep, filepath)->Array.get(1)) {
      | extracted => extracted
      | exception _ => filepath
      };
    } else {
      filepath;
    }
  );

let join = (paths: list(string)): string =>
  List.fold_left((total, next) => Filename.concat(total, next), "", paths);

let basename = Filename.basename;
let dirname = Filename.dirname;
