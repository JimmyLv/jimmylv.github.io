[![Build Status](https://travis-ci.org/JimmyLv/jimmy.lv.svg?branch=gh-pages)](https://travis-ci.org/JimmyLv/jimmy.lv)

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

