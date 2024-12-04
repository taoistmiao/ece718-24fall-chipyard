FROM condaforge/miniforge3 AS base
#stable version
ARG CHECKOUT_HASH=1.13.0

# Install Chipyard and run ubuntu-req.sh to install necessary dependencies
COPY chipyard /chipyard
RUN cd /chipyard && \
        git checkout $CHECKOUT_HASH

FROM base AS chipyard-setup 
SHELL ["/bin/bash", "-cl"]

# Initialize repo
RUN conda install -n base conda-libmamba-solver
RUN conda config --set solver libmamba
# RUN conda init
# RUN conda activate base
RUN cd /chipyard && \
      /bin/bash build-setup.sh riscv-tools -s 6 -s 7 -s 8 -s 9

FROM chipyard-setup AS dev-env
WORKDIR /chipyard/
