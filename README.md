<h1 align="center">
jimmylv.github.io
<h5 align="center", style="color, #666">
:bowtie: Agile Learning based on GitHub issues, KEEP Introspection and Retrospection! 
<br>
基于 GitHub issues 的敏捷学习，持续反思，持续革新，持续进步……
</h5>
</h1>
<p align="center">
<a href="https://travis-ci.org/JimmyLv/jimmylv.github.io"><img src="https://travis-ci.org/JimmyLv/jimmylv.github.io.svg?branch=master" /></a>
<img src="https://img.shields.io/badge/license-MIT-brightgreen.svg" />
</p>

## Using `rake post` to create new post

```shell
rake post title="A Title" [category="category"] [tags=[tag1,tag2]] [description="description"]
```

> ps: this will reate category_imgs and post_imgs directory for this post article. 
> 
> more details in [Rakefile](https://github.com/JimmyLv/jimmy.lv/blob/gh-pages/Rakefile).

## API Support

As you can see in [api](https://github.com/JimmyLv/jimmy.lv/tree/gh-pages/api) folder and generated result in <http://blog.jimmylv.info/api/index.json>.

## Publish Slides

```
nodeppt generate ./_posts/演讲 ./slides -a
```

## Deployment

1. Hosted on [Coding Pages](http://blog.jimmylv.info/).
2. Hosted on [GitHub Pages](http://jimmylv.github.io/).
3. Hosted on [AWS S3](http://blog.jimmylv.info.s3-website-ap-southeast-1.amazonaws.com/).