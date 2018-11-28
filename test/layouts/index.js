import React from "react";
import { hot } from "react-hot-loader";

import Layout from "./layout.gen.js";

const SiteBody = ({ children, location/*, page: { file }*/ }, ctx) => {
  /*
  ReasonReact doesn't support the stateless function 
  context parameter, like used here... therefore we will
  keep the SiteBody as a shim for the ReasonReact app
  
  This is probably the only impediment why we can't migrate to full ReasonReact
  */


  const { router } = ctx;
  return (
    <Layout location={location} router={router}>
      {children}
    </Layout>
  );
};

export default SiteBody;
