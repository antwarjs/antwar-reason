import React from "react";
import Interactive from "../../antwar/dist/Interactive";
import Foo from "../components/Foo";

export default () => {
  return (<div>
      <div> Interactive Component ---v </div>
      <Interactive id="./components/Foo.js" component={Foo} />
    </div>);
};
