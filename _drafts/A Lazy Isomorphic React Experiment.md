---
title: A Lazy Isomorphic React Experiment
tags: []
notebook: 0.0 Inbox
---

# A Lazy Isomorphic React Experiment

#####  [Ali Sheehan-Dare](http://blog.scottlogic.com/asheehan) ·  5th Feb ·  13 min read 

If you’ve used React and Flux, you’ll know how powerful this combination is when building single page applications. But how practical is it when building truly large scale applications with multiple sections? An issue with client-rendered single page applications is the **long initial loading times**, which is particularly noticeable in a multi-page applications, where there is a lot of content to load. Another issue is with **search engine optimisation**, as web crawlers have issues getting information from these applications. I will be discussing both of these in more detail later.

I thought it would be interesting to attempt to build a single page application which behaves like a multi-page application, in a way that would make scaling it a breeze. I wanted to avoid the ‘load everything at launch’ approach of many single page applications and integrate **lazy loading** into the app, which allows the client to load the components, styles for those components, and relevant Redux reducers (or stores in flux) on demand, as the user traverses around the site, massively reducing the initial load time of the application.

## Technologies to include

I wanted to see how well an isomorphic React framework plays with other technologies, meaning how easy it is to incorporate other technologies into the application. I think this is an important gauge of how well this framework would work in practice. So just for reference, here is the list of these technologies/techniques I used.

#### TypeScript

Useful in large applications as the strongly typed nature of it allows you to catch bugs earlier in the development cycle, making it harder to break things when making a change.

#### React-router

Allowing routing to separate ‘pages’ in the application, almost guaranteed in a large application.

#### Redux

A slightly different and more concrete implementation of the flux architecture This is a big topic so I won’t go into much detail in this blog post. If you want to learn more about **Redux** first (which I recommend, its really cool) - [check it out](http://blog.scottlogic.com/2016/01/25/angular2-time-travel-with-redux.html).

#### Hot reloading

This is a hot topic at the moment (I stole that joke from [this blog post](http://blog.scottlogic.com/2016/01/27/a-case-for-hot-reloading.html)). Allows you to streamline your React application development workflow, cutting the time you need to wait for compilation, so definitely check out that blog post if you’re not familiar with the concept, maybe you’ll warm to it (my joke).

#### Sass

And finally, Sass for stylesheets. People have been talking recently about getting rid of stylesheets in React applications altogether, in favour of writing styles in JavaScript then inserting them directly into the react component, with something like [JSS Styles](https://github.com/jsstyles/jss). Maybe that’s for another blog post, so for now, Sass.

## The application

I decided to take the basic Redux shopping cart application as a start point, and adapt it. The application is simple at the moment, but this was more about experimenting with technologies than the end product itself.

The main layout of the website at the moment is as follows:

  1. **Main shop** `/` \- contains the list of products and the current cart. This page sits at the base root.
  2. **Individual product page** `/product/:id` \- This page contains information about a specific product.
  3. **Checkout page** `/checkout` \- Shows the cart only, along with the buy button, which checks out the items and deducts the total from the users balance.


**Check out the code on the [GitHub repository](https://github.com/alisd23/lazy-isomorphic-react)** **And [try the application](http://shopping-cart.alisd.tech/)**

## Why isomorphic?

An isomorphic application is one where the back-end (server) and front-end (client) share the same code. In our React example this means the server and client are both able to render the React components, allowing the client to receive a pre-rendered web page, at which point the client can then take over and start handling the rendering itself.

So why would you develop an isomorphic application?

### 1\. Code reuse

A big benefit is to be able to reduce the amount of overall code in your application. In a server-rendered application you would use a *templating engine* (such as Jade, Blade etc…) to render your markup on the server, and if you wanted to update on the client afterwards you would need some client-side JavaScript logic to do this. With an isomorphic React application you can replace the traditional templating engine with React, allowing you to the use the React components on both the client and the server.

This code reuse could extend even further if you decided to build accompanying mobile apps with **React Native**, because this opens the door for you to share components across web and mobile applications. Whether this is a good thing is still up for debate. Is it a good idea to have multiple applications use the same React component? What if you change a component to address something in the web application, might that break something in your iOS app? Maybe something to consider.

### 2\. Performance

The fact that the server can also render content in **exactly** the same way that the client does means that the initial load time of an isomorphic application would be much smaller than a solely client-rendered application, it would be similar to the load time of a server-rendered application for 2 reasons:

#### No initial render

The client does not have to do the initial render, so this cuts down the amount of processing the client needs to do when the app loads for **the first time**.

#### Smaller initial file size

Thanks to code-splitting the initial file size could also be much smaller, as we only need to load the code for the current page, in the same way you might split your code up for a server-rendered multi-page application.

### 3\. Search engine optimisation

A problem with client-rendered applications currently is that the markup received from the server is pretty much blank, until the client loads and is then able to render the content. This is an issue for web crawlers such as Google’s, as all it can go off initially is your blank page, which won’t do wonders for your search engine presence.

Isomorphic applications solve this problem. By always rendering the page once on the server side before sending it to the client, web crawlers can once again access your real content, just as they would in a server-rendered application.

## Let’s see some Isomorphic Rendering

#### Rendering the application on the server

This rendering code sits inside an express middleware function on the server. We need to use middleware because the user should be able to start at any page on the site, so we have to ‘intercept’ all requests, filter out the ones that are present in our routes definition using the match function (shown later in the code-splitting section), then serve the correct rendered html.

`server/app.tsx`


    
    
    match({ routes, location: req.url || '/' }, (error, redirectLocation, renderProps) => {
      // Compile an initial state (Including react routing information) that will be used
      // to render the correct markup
      const products = {};
      _products.forEach((p) => products[p.id] = p);
      const initialState = {
        products,
        routing: { location: renderProps.location }
      }
      // Initialise store with this state and render the root component (this is the same
      // top-level component which the client will render)
      const store = configureServer(reducerRegistry, initialState);
      const component = (
        
          
            
          
        
      );
    });
    
    // Render the initial html
    // - Store: Place initial state on the browser window object for the client to read on load
    // - assets: Load the relevant assets into the markup using webpackIsomorphicTools
    // - component: The main component to render in the html root
    const html = (
      
    );
    
    res
      .status(200)
      .send('\n' + renderToString(html));



#### Rendering the application on the client:

The client then uses the same process when performing the initial render, it matches the route to make sure it renders the same components as the server did, and mounts it on to the `#root` element.

The initial markup on the client should be **the same** as the markup received from the server. This means React on the client can compare the checksums of the markup, and if they are the same it does not have to render anything initially.

**Note**: The client and the server have different functions for setting up the store. This is simply because there is some extra middleware to be added to the client store specifically for Redux dev tools, which does not work on the server.

`client/app.tsx`


    
    
    match({ history: browserHistory, routes } as any, (error, redirectLocation, renderProps) => {
    
      // Get initial state from window and configure initial state (just like the server)
      const initialState = (window as any).__INITIAL_STATE__;
      const store = configureClient(reducerRegistry, DevTools, initialState);
    
      render(
        
          
            
          
        ,
        document.getElementById('root')
      );
    });



The code above is simplified slightly but as you can see both the client are rendering the exact component, so after this point React takes over and the rendering will be exactly the same on both.

The server has to do a bit more work. It has to embed the assets (JavaScript, styles) into the initial html and also assign the initial state onto the window object so the client can pick it up and initialise its own store.

## Webpack

Webpack is an intelligent module bundler which resolves dependencies in your files and generates the static assets to be delivered to the client. The really great thing about webpack is that these dependencies don’t have to just be standard JavaScript imports or requires. By using specialist **loaders**, you can use webpack to bundle up your Sass into separate modules depending on different entry points in to you application. You could even use webpack to replace the link of `img` elements with base64 strings, hard-coding the image directly inside the react component.

### Sass compilation

Here is an example of using webpack to configure sass compilation, with live reloading.

Webpack config is usually written in a `webpack.config.js` file, so here I tell webpack which loaders to apply to the scss files:

**NOTE** *This is the webpack configuration for the development environment only. You’ll need a separate set of configuration to set the application up for production You can check out my production webpack config* [on GitHub](https://github.com/alisd23/lazy-isomorphic-react/blob/master/webpack/prod.config.js).


    
    
    var config = {
      ...
      module: {
        loaders: [
          ...
          {
            // Only apply loaders to scss files
            test: /\.scss$/,
            // Apply loaders from right to left
            loaders: ['style', 'css', 'sass']
          }
          ...
        ]
      },
    
      // Config for the css-loader
      cssLoader: {
        // True enables local scoped css
        modules: false,
        // Which loaders should be applied to @imported resources (How many after the css loader)
        importLoaders: 1,
        sourceMap: true
      },
      // Config for the sass-loader
      sassLoader: {
        sourceMap: true,
        outputStyle: 'expanded'
      }
    }



Then simply **require** the sass file in your client side JavaScript. which is enough for webpack to realise those styles need loading, so it will then bundle those for you.

So in my `App.tsx` top Level component I require the **common** styles stylesheet


    
    
    class App extends React.Component {
    
      render() : React.ReactElement {
        // Import stylesheet here
        require('../../../sass/common.scss');
    
        return (
          
            
            
            
              {this.props.children}
            
          
        )
      }
    }



### Webpack thoughts

Webpack does a lot. As well as having tons of pluggable loaders to use, there is a plethora of options and configurations, so it’s no doubt that the documentation is a bit… messy. In my opinion it was difficult to find out which configuration options were needed to do certain things. Although the documentation has some decent guides to help with common issues, from my experience there was always more configuration options or things that needed to be done to actually get it working. Often these things weren’t mentioned in the documentation at all.

Of course the documentation is something that I’m sure will be improved in the future as webpack becomes more popular and widely used. Also some of the difficulty came from the fact that webpack and the cool things you can do with it (hot-reloading for example) are fairly new, so the support community and forum questions are lacking at the moment. Again, it’s still early days, so the support material online can only improve from here.

## Lazy-loading and Code splitting

With our isomorphic application having multiple pages, there’s no need for us to load all the assets for the **whole site** on the initial load. We should only load the resources needed for the current ‘page’ we are on.

The assets we are interested in lazy loading are: \- **React components** \- To generate the markup for new pages \- **Stylesheets** \- To style the new components \- **Redux reducers** \- To add functionality to the react components if necessary. I’m using [Redux ducks](https://github.com/erikras/ducks-modular-redux) to separate concerns.

Now ideally what we want is to group related assets together into what webpack calls **chunks**, which is just a chunk of code to be sent to the client. **Code-splitting** is the process of creating split points in the code which webpack can then parse and create modularized output files from. You can tell webpack that there should be a new chunk generated by adding a `require.ensure([], callback)` call into your code (see the [‘time to be lazy’ section](http://blog.scottlogic.com/2016/02/05/a-lazy-isomorphic-react-experiment.html#time-to-be-lazy)), and then `require` modules inside the callback (including sass files if you have the right webpack loader, mentioned above).

There are many plugins and loaders to help with efficiency and different optimisation strategies, some of which are really cool. For example you can easily specify a minimum chunk file size, meaning that any files smaller than the threshold will get merged together, and webpack will sort out all dependencies for you.

You can find the list of webpack plugins [in the webpack documentation](https://webpack.github.io/docs/list-of-plugins.html)

### React router

We’ll do a quick run through of React router to explain how to set up multiple pages in an application, and how it relates to the isomorphic React approach.

We can define routes using a React Router component like the following:


    
    
    import App from './containers/App';
    
    
       {
        // Load all required resources for shop page
      }} />
       {
        // Load all required resources for product page
      }} />
       {
        // Load all required resources for checkout page
      }} />
    



Then by navigating to different urls, React router then loads the correct component and passes in any query parameters as React props. It also plugs easily into the browser history, so the **back** and **forward** buttons work out of the box, transitioning easily between different routes.

### Time to be lazy

You’ll notice for the nested routes that instead of using the `component` prop like the top level **App** route, we supply a `getComponent` prop which is a function, of which one parameter is a callback which the component is passed into.

In this function we can require all the modules we need before the React router switches to the new component, which is exactly what we want. So we end up with a routes file like this:


    
    
    import App from './containers/App';
    
    
       {
        require.ensure([], require => {
          // Retrieve main page component
          cb(null, require('./containers/Main').default);
        });
      }} />
       {
        require.ensure([], require => {
          // Load the product page reducer and add it to the main store
          reducerRegistry.register({ ['productPage']: require('./reducers/productPage').default });
          // Retrieve product page component
          cb(null, require('./containers/Product').default);
        });
      }} />
       {
        require.ensure([], require => {
        // Retrieve checkout page component
          cb(null, require('./containers/CheckoutPage').default);
        });
      }} />
    



**NOTE** the styles are required inside the components themselves. This was a design decision I made due to the fact that styles are so closely related to the React component markup.

Whichever page we start on when loading the app, the correct chunk will be loaded, along with any dependencies (including the stylesheets). Then when you traverse to a different page, the relevant bundle and styles will be loaded for that component too.

### Requiring stylesheets on the server

With a standard webpack configuration, isomorphic applications do not work perfectly in the situation where you want to require stylesheets on the server as well as on the client. Clearly its much more efficient to only include the styles for the initial page we’ve loaded, then lazy load the other styles on demand. However that means we need to be able to bundle stylesheets together on the server too.

**But wait, there’s a problem**

This issue stumped me for a while. As node’s require system doesn’t allow you to require `css` or `sass` files, the server render crashes.

However there is an answer. A helpful (but not particularly easy to implement in my opinion) library called [Webpack Isomorphic Tools](https://github.com/halt-hammerzeit/webpack-isomorphic-tools) solves this problem. It collects all the assets in your components that you want to render, then allows you to render them into the HTML before sending to the client.

This solution isn’t very elegant or easy to find, but I think someone will come up with an even better solution in the future as isomorphic applications grow in popularity.

With the time constraints, I didn’t quite manage to get code-splitting working for the stylesheets, only for the JavaScript files. I think a possible solution is to explicitly define **entry points** in to the application (basically just each individual page the user can start from), then insert the relevant stylesheet links into the initial html being rendered on the server. Then after that webpack should be able to handle the requesting of new style chunks, as you move around the site. Hopefully in the future I’ll be able to add that in, as well as some other improvements.

## To sum it up

I really think that isomorphic applications are the future for multi-page applications, and when combining React, Redux (or something similar), and the likes of webpack with hot-reloading, you have a brilliant JavaScript framework with a clear, structured developer workflow.

However, this is one of the most difficult things I have attempted to build so far. There is a lot of ground work to do before getting to a point where you have this efficient workflow. But when you get there, it’s worth it.

From what I’ve seen so far, a lot of this stuff is still quite ‘cutting edge’, so don’t expect a million Stack Overflow questions and tons of examples online. You might have to go digging through some code… This also means it is very likely to change in the future, so take that under consideration before starting a production application in this way.

Again, if you want to have a look at the code I’ll leave a link to the [GitHub repository](https://github.com/alisd23/lazy-isomorphic-react), and you can try out the application [here](http://188.166.136.217/)
