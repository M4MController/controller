# M4M Controller
## Running
1. Install [libmbus](https://github.com/samkrew/libmbus)
```bash
# download libmbus
git clone https://github.com/samkrew/libmbus

# install autoheader dependency
sudo apt install autotools-dev

# build and install libmbus
cd libmbus
./build.sh
make
sudo make install
cd ..

# remove unnecessary sources
rm -rf libmbus

# create symlink to library
sudo ln -s /usr/local/lib/libmbus.so.0 /usr/lib/libmbus.so.0
```

2. Build the app
```bash
npm i
```

3. Run
```bash
npm start
```