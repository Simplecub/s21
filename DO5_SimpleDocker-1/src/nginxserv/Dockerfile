FROM nginx
WORKDIR /home
RUN apt-get update
COPY nginx/nginx.conf ../etc/nginx/nginx.conf
CMD nginx -g 'daemon off;'
