module Node = {
  type childProcess;

  [@bs.module "child_process"]
  external _spawn: (~exe: string, ~args: array(string)) => childProcess = "spawn";

  [@bs.send]
  external onClose: (childProcess, [@bs.as "close"] _, int => unit) => unit =
    "on";

  let spawn = (~exe: string, ~args: array(string)): Js.Promise.t(int) =>
    Js.Promise.make((~resolve, ~reject) =>
      _spawn(~exe, ~args)->onClose(code => resolve(. code))
    );
};
