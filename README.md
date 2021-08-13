# yuvplayer

Lightweight YUV player which supports various YUV format

Supporting Format
* Planar format
* YUV420 (YV12)
* YUV422 (YV16)
* YUV444
* RGB16
* RGB24
* RGB32


* Interleaved format
* NV12
* NV21
* UYVY
* VYUY

Supporting Feature
* Zoom (4:1 ~ 1:4)
* Store frame to YUV/BMP

Hot key
* "→": frm-forward
* "←": frm-backward
* "↑": zoom-in
* "↓": zoom-out
* "p/space": play/pause toggle
* "o": open
* "g": goto a frame
* "x": exit
* "h" set size to 1080p(HD)
* "s" set size to 720p(SD)
* "c" set size to CIF
* "q" set size to QCIF
  
Command Line
* "-s": size, example: 128x128
* "-z": zoom, one of: 4:1, 2:1, 1:1, 1:2, 1:4
* "-c": color, one of: YUV420_10BE, YUV420_10LE, YUV444, YUV422, YUV420, UYVY, YUYV, YYY, PACKED_YUV444, NV12, NV21, RGB32, RGB24, RGB16