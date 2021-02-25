FROM docker.io/eltuercas/drogon

# Create application directory
WORKDIR /aweb-proj

# Copy licence
COPY ./LICENSE /aweb-proj/LICENSE

# Copy npm package description and install npm dependencies
COPY ./package.json /aweb-proj/package.json
COPY ./package-lock.json /aweb-proj/package-lock.json
RUN npm install

# Copy release configuration file
COPY ./releaseconfig.json /aweb-proj/config.json

# Source SCSS files
COPY ./scss /aweb-proj/scss

# Source TS files and configuration
COPY ./ts /aweb-proj/ts
COPY ./tsconfig.json /aweb-proj/tsconfig.json

# Tailwind CSS config file
COPY ./tailwind.config.js /aweb-proj/tailwind.config.js

# Mix asset file
COPY ./webpack.mix.js /aweb-proj/webpack.mix.js

# Copy CMakeLists
COPY ./CMakeLists.txt /aweb-proj/CMakeLists.txt

# Copy C++ source files
COPY ./main.cc /aweb-proj/main.cc
COPY ./controllers /aweb-proj/controllers
COPY ./plugins /aweb-proj/plugins
COPY ./filters /aweb-proj/filters

# Copy CSP files
COPY ./views /aweb-proj/views

# Copy database model spec file and C++ model source files
COPY ./models /aweb-proj/models

# Create webpack production files
RUN npm run prod

# Change to build directory and compile the application
WORKDIR /aweb-proj/build
RUN cmake -DCMAKE_BUILD_TYPE=Release -DCMAKE_CXX_FLAGS="-fcoroutines" ..
RUN make

# Create a symlink to be able to serve the fonts since otherwise it no worky
RUN ln -s /aweb-proj/node_modules/\@iconsout/unicons/fonts /aweb-proj/fonts

# Run web application
CMD ["/aweb-proj/build/aweb-1smr-2nd-term-project"]