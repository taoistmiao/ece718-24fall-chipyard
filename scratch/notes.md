docker build -f Dockerfile -t your-tag-name
docker save your-tag-name -o your-tarball-name.tar
docker image rm your-tag-name
apptainer build --fakeroot your-sif-name.sif docker-archive://your-tarball-name.tar
rm your-tarball-name.tar
https://apptainer.org/docs/user/main/persistent_overlays.html#overlay-embedded-in-sif
apptainer overlay create --fakeroot --size 1024 overlay.img
apptainer shell -C -B ece718-24fall-chipyard:/ece718-24fall-chipyard --fakeroot --overlay overlay.img chipyard-env.sif