REGISTRY = wyga/ws-echo
PLATFORM = linux/amd64,linux/arm64
OUTPUT = --output type=image,push=true,compression=gzip
BUILDX = docker buildx build --provenance false $(OUTPUT) --platform $(PLATFORM) --builder multiplatform-builder
all:
	$(BUILDX) -f Dockerfile -t $(REGISTRY):latest .
