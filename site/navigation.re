type state = unit;
type action = unit;

let component = ReasonReact.reducerComponent(__MODULE__);

let make = _children => {
  ...component,
  initialState: () => (),
  reducer: (action: action, state: state) => ReasonReact.NoUpdate,
  render: _self =>
    <div>
      <div> "Home"->ReasonReact.string </div>
      <div> "About"->ReasonReact.string </div>
    </div>,
};
