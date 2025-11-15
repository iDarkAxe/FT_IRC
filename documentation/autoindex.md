# Autoindex on : feature #

`autoindex [on|off];` can be found in a location directory.

`autoindex_exact_size [on|off];` : For the HTML format, specifies whether exact file sizes should be output in the directory listing, or rather rounded to kilobytes, megabytes, and gigabytes. We can set `--noreport` to `tree` to enable or disable.

`autoindex_localtime [on|off];` : For the HTML format, specifies whether times in the directory listing should be output in the local time zone or UTC. We can set `-D` to add the date of last modification or (`-c`) status change.

`autoindex_format [html|xml|json|jsonp];` : Sets the format of a directory listing.

To have autoindex work, we need to create a listing of files, and folders from the requested directory, we could use a simple command to execute the following command to generate the listing.

```sh
tree -H '.' -L 1 --noreport --dirsfirst -T 'Downloads' -s -D --charset utf-8 -I "index.html" -o index.html
```

* `-H '.'` : prints in HTML format
* `-L level` : is to precise how many level of directory to list
* `-T 'string'` : replace the title and h1 header with string
* `-s` : is to print the size in bytes of each file.
* `-D` : is to print the date of last modification or status change.
* `--dirsfirst` : is to list directories before files
* `--noreport` : is to turn off file/directory count at end of tree listing
* `-I pattern` : is to not include certain files/folders that match pattern
* `-o filename` : is to write output to a file, but in a cgi we should redirect all output to client


Syntax: 	autoindex_exact_size on | off;
Default: 	

autoindex_exact_size on;

Context: 	http, server, location

For the HTML format, specifies whether exact file sizes should be output in the directory listing, or rather rounded to kilobytes, megabytes, and gigabytes. 