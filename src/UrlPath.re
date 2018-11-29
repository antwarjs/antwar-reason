type t = list(string);

let toUrl = (urlPath: t): string =>
  switch (urlPath) {
  | [] => "/"
  | multiple => List.fold_left((acc, str) => acc ++ "/" ++ str, "", multiple)
  };

let toFilepath = (urlPath: t): string =>
  switch (List.rev(urlPath)) {
  | [name, ..._rest] => name ++ ".html"
  | _ => "index.html"
  };
