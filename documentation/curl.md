# Curl #

## Using curl, you can make request easily ##

* `-X PROTOCOL` : Protocol can be GET, POST, DELETE, PATCH...
* `--http1.0` : precise which http version we want to use
* `-v` : makes curl more talktative and prints the whole request AND answer, not only bodies
* `-k` : makes the use of self certificate acceptable
* `-H or --header` : @filename or "content" to add content to the header
* `-d or --data` : @filename or "content" to pass data to the body of the request
* `--useragent "firefox"` : user-agent to simulate, the user-agent of Zen Browser (Mozilla Firefox fork) by default on Ubuntu 22.04 is : `Mozilla/5.0 (X11; Linux x86_64; rv:144.0) Gecko/20100101 Firefox/144.0`.

## Example ##

```sh
$> curl -v --http1.0 --user-agent "firefox" --header "Content-length: 0" --request GET info.cern.ch

Note: Unnecessary use of -X or --request, GET is already inferred.
*   Trying 188.184.67.127:80...
* Connected to info.cern.ch (188.184.67.127) port 80 (#0)
> GET / HTTP/1.0
> Host: info.cern.ch
> User-Agent: firefox
> Accept: */*
> Content-length: 0
> 
* Mark bundle as not supporting multiuse
< HTTP/1.1 200 OK
< Date: Thu, 23 Oct 2025 10:57:46 GMT
< Server: Apache
< Last-Modified: Wed, 05 Feb 2014 16:00:31 GMT
< ETag: "286-4f1aadb3105c0"
< Accept-Ranges: bytes
< Content-Length: 646
< Connection: close
< Content-Type: text/html
< 
<html><head></head><body><header>
<title>http://info.cern.ch</title>
</header>

<h1>http://info.cern.ch - home of the first website</h1>
<p>From here you can:</p>
<ul>
<li><a href="http://info.cern.ch/hypertext/WWW/TheProject.html">Browse the first website</a></li>
<li><a href="http://line-mode.cern.ch/www/hypertext/WWW/TheProject.html">Browse the first website using the line-mode browser simulator</a></li>
<li><a href="http://home.web.cern.ch/topics/birth-web">Learn about the birth of the web</a></li>
<li><a href="http://home.web.cern.ch/about">Learn about CERN, the physics laboratory where the web was born</a></li>
</ul>
</body></html>
<!doctype html><html>
[...]
</html>
```

* `Note:` is a comment about the argument of command
* `*` is a comment about what curl is doing
* `<` is what the client send to the server.
* `>` is what the server answered
