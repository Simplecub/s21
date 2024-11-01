#!/bin/bash

gcc -o web miniserv.c -lfcgi
spawn-fcgi -p 8080 web
nginx -g 'daemon off;'
