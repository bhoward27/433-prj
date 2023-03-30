# Makefile from edge-impulse example Makefile

OUT_DIR = $(HOME)/cmpt433/public/myApps
NODE_COPY_PATH = $(OUT_DIR)/server-copy

all: node

# Deploy and install node files
node: node_deploy node_install

node_deploy:
	@echo 'COPYING THE NODE.JS FILES TO $(NODE_COPY_PATH)'
	@echo ''
	mkdir -p $(NODE_COPY_PATH)
	chmod a+rwx $(NODE_COPY_PATH)
	cp -rf NodeJs-Code/* $(NODE_COPY_PATH)

	@echo 'Do not edit any files in this folder; they are copied!' > $(NODE_COPY_PATH)/DO_NOT_EDIT-FILES_COPIED.txt
	@echo ''
	@echo 'NOTE: On the host, in $(NODE_COPY_PATH), it is best to run: npm install'
	@echo '      Or, just run the node_install target in this makefile.'

node_install:
	@echo ''
	@echo ''
	@echo 'INSTALLING REQUIRED NODE PACKAGES'
	@echo '(This may take some time)'
	@echo ''
	cd $(NODE_COPY_PATH) && npm install
