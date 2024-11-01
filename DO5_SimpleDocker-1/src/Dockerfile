FROM nginx:latest
WORKDIR /home/

COPY /server/nginx/nginx.conf /etc/nginx/nginx.conf
COPY /server/miniserv.c /home/miniserv.c
COPY start.sh /home/start.sh
RUN apt-get update; \
    apt-get install -y gcc libfcgi-dev spawn-fcgi; \
    chown -R nginx:nginx /home; \
    chown -R nginx:nginx /etc/nginx/nginx.conf; \
    chown -R nginx:nginx /var/cache/nginx; \
    touch /var/run/nginx.pid; \
    chown -R nginx:nginx /var/run/nginx.pid; \
    chmod +x start.sh; \
    chmod u-s /usr/bin/gpasswd; \
    chmod u-s /usr/bin/su; \
    chmod g-s /usr/bin/expiry; \
    chmod u-s /usr/bin/mount; \
    chmod g-s /usr/bin/wall; \
    chmod g-s /usr/bin/chage; \
    chmod u-s /usr/bin/chfn; \
    chmod u-s /usr/bin/passwd; \
    chmod g-s /usr/sbin/unix_chkpwd; \
    chmod u-s /usr/bin/chsh; \
    chmod u-s /usr/bin/newgrp; \
    chmod u-s /usr/bin/umount; \
    rm -rf /var/lib/apt/lists
USER nginx
HEALTHCHECK --interval=20s --start-period=5s --timeout=3s CMD curl localhost:80 || exit 1

ENTRYPOINT bash start.sh
