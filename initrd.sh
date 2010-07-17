sz=`du out/kernel -b`
sz=${sz%%out*}
sz=$(( (sz / 512 + 1) * 512 - $sz))
dd if=/dev/zero of=$1 bs=1 count=$sz > null
