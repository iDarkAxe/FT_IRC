# Siege #

Outil de test de charge sur un serveur web, permet de simuler de grande quantités de clients simultanés. Pour un bon score il faut une disponibilité supérieure à 99%.

## Usage ##

```sh
siege [options] URL
```

* `-c` or `--concurrent=NUM` : number of concurrent users
* `-r` or `--reps=NUM` : number of times to run the test
* `-d` or `--delay=NUM` : delay between request
* `-b` or `--benchmark` : mode benchmark, no delays
* `-H` or `--header="text"` : Add a header to request (can be many)
* `-A` or `--user-agent="text"` : Sets User-Agent in request

```sh
siege -b -c 100 localhost:port/index.html
```
