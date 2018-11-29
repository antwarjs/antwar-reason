open Common;

let concatUrlPath = (urlPath: url_path): string =>
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
