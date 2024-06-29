# syntax=docker/dockerfile:1.6
FROM alpine AS mold
ARG TARGETARCH
COPY --chmod=0755 binary/ws-server.${TARGETARCH} /mold/ws-server

FROM scratch
COPY --from=mold /mold/ /
EXPOSE 8000
ENTRYPOINT [ "/ws-server" ]
