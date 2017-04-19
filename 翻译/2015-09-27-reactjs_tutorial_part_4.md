---
layout: post
title: 【译】React.js教程 第四部分：Express路由
categories: [翻译]
tags: [React, Express]
published: True

---

技术系列笔记均已迁移至GitBook，更多`React`的内容请到：<http://jimmylv.gitbooks.io/learning-react-js/content/reactjs_tutorial/reactjs_tutorial_part_4.html>

# *React*.js Tutorial Part 4

原文地址：<http://www.joshfinnie.com/blog/reactjs-tutorial-part-4/>

> Welcome to part 4 of my *React*.js/Express.js app tutorial. In this blog post, we are going to create the necessary Express routes to serve `json` code to our *React*.js frontend application. We are also going to very rudimentarily hook up these calls to our server it our *React*.js component so that the `json` can be rendered.

欢迎来到React.js/Express.js教程的第四部分。在这篇博客文章里，我们将会创建必要的Express路由来将`json`代码提供给我们的*React*.js前端应用程序使用。我们也准备让*React*.js组件得以初步调用我们的服务器，以便于`json`数据可以被渲染。

## Express Routes | Express 路由

> The first thing we want to do is to create an Express.js route that will serve a `json` response when a certain URL is hit. This is actually very easy to accomplish within the Express.js framework. The setup of the Express.js website, which was auto-generated for us in [Part 1 of this tutorial](http://www.joshfinnie.com/blog/reactjs-tutorial-part-1/) does a good job of getting us started, but to continue, we want to add some more files to help keep things organized for us. 

我们想要做的第一件事情就是创建一个Express.js路由，以便于一个具体的URL被点击的时候返回一个`json`。通过Express.js框架很轻松就可以达成目标。关于安装Express.js网站，在[教程的第一部分](http://www.joshfinnie.com/blog/reactjs-tutorial-part-1/)已经为我们自动生成了，可以很好地用于入门。但是接下来，我们想要添加一些文件来保持组织性。

> So before anything else we want to create another file to keep our API routes. This file will be called `routes/api.js` simply enough. Then we have to edit `app.js` a bit to make sure we can use this new file. In `app.js` we want to modify `var routes = require('./routes/index');` to be something a little more useful to us: `var index = require('./routes/index');`. Then directly below that we want to add our new API routes: `var api = require('./routes/api');`. Lastly, we want to add these to our `app` by adding: `app.use('/api/', api);`. Our `app.js` file should, partially, look like this:

所以在其他事情开始之前，我们想要创建另外的文件来存放API路由。这个文件叫做`routes/api.js`就可以了，然后我们就需要稍微改变一下`app.js`来保证我们可以使用新文件。在`app.js`中，我们把`var routes = require('./routes/index');`修改成其他更有用的形式：`var index = require('./routes/index');`。然后直接在底下添加想要的新的API路由：`var api = require('./routes/api');`。最后，把这些东西添加至`app`：`app.use('/api/', api);`。我们的`app.js`就应该有点模样了：

    ...
    
    var index = require('./routes/index');
    var api = require('./routes/api');
    
    ...
    
    app.use('/', index);
    app.use('/api/', api);
    
    ...
    

> Now we can add a `jobs` route to our `routes/api.js` and start serving `json` through our Express.js app.

现在我们可以添加`jobs`路由到我们`routes/api.js`，然后通过Express.js应用提供`json`。

### API Routes | API 路由

> There are a lot of resources out there about "Restful" API structure, but [Tuts+](http://code.tutsplus.com/tutorials/a-beginners-guide-to-http-and-rest--net-16340) does a pretty good job and I don't want to dedicate too much time to it; this part of the tutorial does not really need a lot of REST endpoints.

这儿有很多关于"Restful" API架构的资源，而[Tuts+](http://code.tutsplus.com/tutorials/a-beginners-guide-to-http-and-rest--net-16340)就是一个非常棒的教程，我不想再花费太多时间去解释它了。本教程的这部分其实也不需要非常多的REST端口。

> But let's write our first `GET` endpoint which will list out all the jobs we have available. First, we want to steal the `jobs` object from our *React*.js code and move it into `routes/api.js` then we want an endpoint that will return that object is `json` form. This is done by the following code:

但是让我们来写第一个`GET`端口，用于列举已有的所有工作信息。首先，我们想要从*React*.js代码中把`jobs`对象拿出来，然后放到`routes/api.js`里，从而我们就需要一个端口可以返回`json`形式的对象。通过以下代码可以实现：
    
    var express = require('express');
    var router = express.Router();
    
    var jobs = {
        jobs: [
            {
                job_id: 1,
                company: 'TrackMaven',
                position: 'Software Maven',
                local: 'Washington, DC, USA',
                lookingFor: '*Angular*.js, Django, ElasticSearch',
                postedDate: '4 April 2015',
                description: '',
                category: 'Engineering'
            },
            {
                job_id: 2,
                company: 'TrackMaven',
                position: 'Junior Software Maven',
                local: 'Washington, DC, USA',
                lookingFor: 'Javascript, Python',
                postedDate: '4 April 2015',
                description: '',
                category: 'Engineering'
            }
        ]
    }
    
    router.get('/jobs', function(req, res) {
        res.json({data: jobs});
    });
    
    module.exports = router;
    

> The object is almost a direct copy that we had hardcoded within our *React*.js app, with a few modifications. Most importantly, we added the `job_id` variable. This will allow us to use our REST endpoints to return only one job posting, if we want to... which of course we do.

这个对象几乎就是一个直接拷贝，在*React*.js应用进行硬编码的基础之上带有一点儿修改。最重要的是，我们添加了`job_id`变量。这可以让我们使用REST端口，只返回唯一的工作岗位，如果我们想要……当然我们也做了。

> To do that, it's actually pretty simple. Using Express.js's ability to know what URL parameters hit each endpoint, we can add an endpoint that looks like `/api/jobs/1` and our router will know that we want the job with `job_id == 1`. To do this, add the following to `routes/api.js`:

做到这样实际上非常简单。使用Express.js可以知道每个端口中含有哪些URL参数，我们可以添加一个像`/api/jobs/1`这样的端口，然后我们的路由就会知道我们想要`job_id == 1`的这个工作信息。为此，可以给`routes/api.js`添加以下代码：

    router.get('/jobs/:job_id', function(req, res) {
        var job_id = req.params.job_id;
        for (i = 0, len = data.jobs.length; i < len; i++) {
            if (data.jobs[i].job_id === parseInt(job_id)) {
                res.json({data: job});
            }
        }
        res.json({data: "No job found..."});
    });

> **Please Note**: This is not ideal, nor really even practical. In the real world, we would be searching for the `job_id` in a database, not this silly `for -> if` statement we are doing here. But that's for a later tutorial!

**请注意**：这并不合适，也不具有可实践性。事实上，我们将会从数据库中查找`job_id`，而不是像我们这样很傻地使用`for -> if`语句。但那是之后的教程了！

> With these two routes, we should be able to `curl` these two endpoints and get the following results:

通过这两个路由，我们就应该可以使用`curl`来访问这两个端口，得到以下结果：
    
    $ curl localhost:3000/api/jobs
    {"data":{"jobs":[{"job_id":1,"company":"TrackMaven","position":"Software Maven","local":"Washington, DC, USA","lookingFor":"*Angular*.js, Django, ElasticSearch","postedDate":"4 April 2015","description":"","category":"Engineering"},{"job_id":2,"company":"TrackMaven","position":"Junior Software Maven","local":"Washington, DC, USA","lookingFor":"Javascript, Python","postedDate":"4 April 2015","description":"","category":"Engineering"}]}}
    
    $ curl localhost:3000/api/jobs/1
    {"data":{"job_id":1,"company":"TrackMaven","position":"Software Maven","local":"Washington, DC, USA","lookingFor":"*Angular*.js, Django, ElasticSearch","postedDate":"4 April 2015","description":"","category":"Engineering"}}
    
    $ curl localhost:3000/api/jobs/2
    {"data":{"job_id":2,"company":"TrackMaven","position":"Junior Software Maven","local":"Washington, DC, USA","lookingFor":"Javascript, Python","postedDate":"4 April 2015","description":"","category":"Engineering"}}
    

> That's it! We have a very basic API that we can now have our *React*.js code talk to.

就是这样！我们有了一个非常基础的API，现在我们可以让*React*.js代码与之交互了。

## *React*.js and APIs | *React.js* 和 APIs

> When first interacting with APIs using *React*.js, I recommend just using the `request` packages. We will need to add this to our application, but that's as easy as running `npm install request --save`.

第一次使用*React*.js与APIs交互的时候，我推荐使用`request`包就好了。我们需要把它添加至应用程序，但是只要简单运行一下`npm install request --save`。

> Once we have the `request` library installed, we need to do some modification to our `public/javascripts/scr/Jobs.jsx` file to get the data from our API. To do this, we need to slightly modify the `getInitialState` function and add the `componentDidMount` function. We no longer have an full initial state (just a skeleton of what we want our API to look like) since we want to get the data from the API once the component mounts to our application. Our entire `public/javascripts/scr/Jobs.jsx` now looks like this:

只要我们安装好了`request`库，我们还需要为`public/javascripts/scr/Jobs.jsx`文件做一些修改，得以从API中获取数据。为此，我们需要小小地修改一下`getInitialState`函数，并且添加`componentDidMount`函数。我们不再需要完整的初始化状态（就像我们需要的API标本那样），因为我们期望组件在装配到应用程序的时候就从API中获取数据。我们整个`public/javascripts/scr/Jobs.jsx`文件现在长这样：

```jsx    
    var React = require('react');
    var request = require('request');

    var Job = require('./Job.jsx');

    module.exports = React.createClass({
        getInitialState: function() {
            return {jobs: []}
        },

        componentDidMount: function() {
            request('http://localhost:3000/api/jobs/', function(error, response, body) {
                var result = JSON.parse(body);
                if (this.isMounted()) {
                    this.setState(result.data);
                }
            }.bind(this));
        },

        render: function(){
            return (
                <div className="list-group">
                    {this.state.jobs.map(function(job){
                        return (
                            <Job
                                key={job.job_id}
                                company={job.company}
                                position={job.position}
                                local={job.local}
                                lookingFor={job.lookingFor}
                                postedDate={job.postedDate}
                                description={job.description}
                                category={job.category}
                            />
                        )
                    })}
                </div>
            );
        }
    });
```

> In the file above, you can see how we are using the `request` library to reach out to our newly created API and populate the `state` with the response. You can also see the modifications we made to `render` to allow for us to use the API. And that's it, we should still have a working website that renders these two jobs, but now we are getting data from an API versus hardcoding it within our *React*.js component (even though we are still just hardcoding it within our API).

在上面的文件里，你可以看到我们如何使用`request`库从新建的API中获取到数据，并将返回值放入`state`中。你也可以看到我们在`render`中做了修改，使我们可以使用这个API。就是这样，我们还是拥有一个可工作的网站，并且渲染了这两个工作信息，但是现在我们的*React*.js组件是从API中获取数据，而不再是硬编码的（尽管我们的API里面还是硬编码的）。

## Conclusion | 结论

> With this part of our tutorial, we have our app now using the API to populate its data. We have a long road ahead before this actually becomes useful, but it's a great start. Next time we will be introducing a way of routing in *React*.js so that we can not only see all the job posts, but we can drill down to each specific job post. We also need to hook up a database and start collecting data from *React* too. Please stay tuned!

通过这部分的教程，我们让应用程序通过API来获取它的数据。长路漫漫，其修远兮，但这是一个非常棒的开始。下一次我们会介绍在*React*.js里的路由方式，以便于我们不仅可以看到所有的工作岗位，还可以进一步查看每个特定的工作信息。我们还需要连接到数据库，并且从*React*中收集数据。请保持步调一致哟！
