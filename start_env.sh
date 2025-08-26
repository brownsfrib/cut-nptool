#!/usr/bin/bash

###########################################
# Starting shellrc for contained analysis #
###########################################
export imgBuster="/usr/opt/nscl-buster.img"
export imgName="CFFD"
export basePath="$(pwd)"



echo -e "\033[1;35mStarting Buster container (sourcing $basePath/.shellrc)\033[0m"
export SINGULARITY_SHELL=/bin/bash
singularity shell --pwd $basePath --workdir $basePath \
	--bind /usr/opt/opt-buster:/usr/opt/,/mnt/misc/sw/indep \
	--bind /mnt/misc/sw/x86_64/all \
	--bind /usr/lib/x86_64-linux-gnu/modulecmd.tcl \
	$imgBuster --rcfile $basePath/.shellrc
