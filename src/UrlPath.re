type t = list(string);

let toUrl = (urlPath: t): string =>
  switch (urlPath) {
  | [] => "/"
  | _ =>
    List.fold_left(
      (acc, str) =>
        switch (acc) {
        | "" => str
        | _ => "/" ++ str
        },
      "",
      urlPath,
    )
  };


let toFilepath = (urlPath: t): string =>
  switch (List.rev(urlPath)) {
  | [name, ..._rest] => name ++ ".html"
  | _ => "index.html"
  };
