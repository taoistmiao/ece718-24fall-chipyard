FROM condaforge/miniforge3 AS base
#stable version
ARG CHECKOUT_HASH=ece718-24fall

# Install Chipyard and run ubuntu-req.sh to install necessary dependencies
# COPY .. /chipyard
RUN git clone https://github.com/taoistmiao/ece718-24fall-chipyard.git /chipyard
# RUN git clone git clone https://github.com/ucb-bar/chipyard.git /chipyard
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
