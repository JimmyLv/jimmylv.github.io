# Jekyll REST API

This is a read only JSON API, making it easier to connect third party systems
to your content, or do more advanced renderings with javascript on your jekyll site
that can't be done with the liquid syntax.

### Table of contents
- [Ideas of what you can build with this API](#ideas-of-what-you-can-build-with-this-api)
- [Installation](#Installation)
	- [Via git submodule](#via-git-submodule)
	- [Via bower](#via-bower)
- [Output examples](#output-examples)
	- [posts.json](#postsjson)
	- [settings.json](#settingsjson)

### Ideas of what you can build with this API:
- Search trough **all** your Jekyll posts with javascript, without having to
    parse the HTML.
- Define settings for your javascript via your `_config.yml`.
- Create a javascript code that will alert the user on the screen when
    there is a new post available.
- Apply filters to the post content before rendering, such as wrapping all
    images in a different code for a lightbox system.

# Installation

#### Via git submodule

###### Installing
```bash
git submodule add 'https://github.com/riichard/jekyll-rest-api'
```

###### Usage
```
http://myjekyllsite.com/jekyll-rest-api/posts.json
```
This also works like a charm on `.github.io` URLs. 

#### Via bower

###### Installing
```bash
bower install jekyll-rest-api
```

####### Usage
```
http://myjekyllsite.com/bower_components/jekyll-rest-api/posts.json
```

# Output examples

All output examples can also be found in the `output-example` folder.

### /posts.json
```json
[
		{
            "id"         : "/The unique ID of the post",
            "title"      : "The title of the post",
            "category"   : "demo",
            "tags"       : "demo,test",
            "url"        : "/url-according-to-config-defined-formatting",
            "path"       : "_posts/2015-07-21-demo.md",
            "next"       : "/path-to-next-post-or-empty-string",
            "previous"   : "/path-to-previous-post-or-empty-string",
            "date"       : "2015-07-26 04:00:00 -0400",
            "shortdate"  : "July 26, 2015",
            "content"    : "&lt;p&gt;Escaped content&lt;/p&gt;",
            "excerpt"    : "&lt;p&gt;First paragraph of post&lt;/p&gt;",
		} 
        ....
]
```

### /settings.json
```json
{
    "title": "Richard A. Kraaijenhagen",
    "description": "Full Stack Developer & Data Scientist/Visualizer. Founder Owlin.",
    "default_bg": "avatar_45.jpg",
    "search": "true",
    "share": "true",
    "readtime": "true",
    "wpm": "200",
    "baseurl": "",
    "fin_color": "255,255,255",
    "timezone": "America/New_York",
    "encoding": "utf-8",
    "categories": [
        "owlin"
    ],
    "tags": [
        "owlin",
        "vim"
    ],
}
```
This will contain all keys defined in `_config.yml`. Due to a conflict with jekyll, this file couldn't be named `config.json` but is named `settings.json` instead.
