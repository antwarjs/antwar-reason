open Util;
let component = ReasonReact.statelessComponent(__MODULE__);

[@genType]
let make = (_children) => {
  ...component,
  render: _self => {
    <div>"Bar Test"->s</div>
  }
};
