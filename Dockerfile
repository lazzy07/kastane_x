# ---------- build stage (has compilers & CMake) -----------------------------
FROM nvidia/cuda:12.9.1-cudnn-devel-ubuntu24.04 AS dev
RUN apt-get update && \
    apt-get install -y --no-install-recommends cmake ninja-build g++ && \
    rm -rf /var/lib/apt/lists/*
WORKDIR /workspace

# ---------- runtime stage (tiny, optional) ----------------------------------
FROM nvidia/cuda:12.9.1-cudnn-runtime-ubuntu24.04 AS run
WORKDIR /app
COPY --from=dev /workspace/dist/kastane_x .
CMD ["./kastane"]