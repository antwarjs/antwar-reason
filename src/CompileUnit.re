module Make = (Component: {type t;}) => {
  type bundle = {
    id: string,
    entry: string,
  };

  type page = {
    urlPath: UrlPath.t,
    component: Component.t,
  };

  type t =
    | Page(page)
    | Bundle(bundle);
};
