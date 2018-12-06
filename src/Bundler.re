/*
    This module contains helpful structures for spawning bundler processes.
    Mostly we want to have type-checked cmd strings, these modules make sure
    to provide the correct argument behavior etc.
 */
module Fastpack = {
  type t = {
    exe: string,
    args: array(string),
  };

  type task =
    | Build
    | Serve;

  let taskToStr = (task: task) =>
    switch (task) {
    | Build => "build"
    | Serve => "serve"
    };

  let make =
      (
        ~useNpx=true,
        ~task=Build,
        ~dev=true,
        ~entry: string,
        ~output="./bundle",
        ~name="index.js",
        ~preprocess: list(string)=[],
        (),
      )
      : t => {
    let (exe, args) =
      if (useNpx) {
        ("npx", [|"fpack"|]);
      } else {
        ("fpack", [||]);
      };

    let addArg = arg => Js.Array.push(arg, args) |> ignore;
    let addArgs = (more: list(string)) =>
      List.iter(arg => addArg(arg), more);

    addArgs([taskToStr(task), entry, "-n " ++ name]);

    if (dev) {
      addArg("--development");
    };

    switch (preprocess) {
    | [] => ()
    | options =>
      List.iter(str => addArg("--preprocess=\"" ++ str ++ "\""), options)
    };

    switch (output) {
    | str => addArgs(["-o", str])
    | _ => ()
    };

    {exe, args};
  };

  let toString = (config: t) => {
    let {exe} = config;

    let args =
      Js.Array.reduce(
        (ret, next) =>
          switch (ret) {
          | "" => next
          | str => str ++ " " ++ next
          },
        "",
        config.args,
      );

    {j|$exe $args|j};
  };

  let exec = (config: t): Js.Promise.t(int) => {
    let {exe, args} = config;
    Process.Node.spawn(~exe, ~args);
  };
};
