[%raw
"require('../styles/main.css')"];

module Interactive = Antwar.Interactive;

module Helmet = ReactHelmet.Helmet;
module Link = ReactRouterDom.Link;

let component = ReasonReact.statelessComponent("Layout");

let siteName = "Antwar Reason Test";

[@genType]
type file = {
  title: string,
  description: string,
  keywords: array(string),
};

[@genType]
type location = ReactRouter.location;

[@genType]
let make = (~_location: location/*, ~_file: file*/, children) => {
  ...component,
  render: _self => {
    <div className="root">
      /* <Interactive */
        /*id="components/InteractiveNavigation.gen.js"*/
        /*container={<InteractiveNavigation location />}*/
        /*props={"location": location}*/
      /* />*/
      <main>
        <Bar/>
        children
      </main>
    </div>;
  },
};
