project(
  'mm-radio',
  ['c', 'cpp'],
  version : '',
  license : 'APACHE-2.0',
  meson_version : '>= 0.56',
  default_options : ['buildtype=debugoptimized', 'b_ndebug=if-release', 'c_std=c11', 'cpp_std=c++17', 'cpp_rtti=false']
)

srcs = [
    'src/RadioConfig.cpp',
    'src/RadioData.cpp',
    'src/RadioMessaging.cpp',
    'src/RadioModem.cpp',
    'src/RadioNetwork.cpp',
    'src/RadioSim.cpp',
    'src/RadioVoice.cpp',
    'src/service.cpp',
]

cflags = ['-Wno-unused-parameter']

deps = [
    dependency('cutils'),
    dependency('android.hardware.radio-V1-ndk'),
    dependency('android.hardware.radio.config-V1-ndk'),
    dependency('android.hardware.radio.data-V1-ndk'),
    dependency('android.hardware.radio.messaging-V1-ndk'),
    dependency('android.hardware.radio.modem-V1-ndk'),
    dependency('android.hardware.radio.network-V1-ndk'),
    dependency('android.hardware.radio.sim-V1-ndk'),
    dependency('android.hardware.radio.voice-V1-ndk'),
]

executable(
    'android.hardware.mm-radio-service',
    srcs,
    dependencies : deps,
    install : true,
    install_dir : get_option('bindir') / 'hw',
)

configure_file(
    input: 'android.hardware.radio.rc',
    output: '@PLAINNAME@',
    copy: true,
    install_dir: get_option('sysconfdir') / 'init',
)

configure_file(
  input: 'android.hardware.radio.xml',
  output: '@PLAINNAME@',
  copy: true,
  install_dir: get_option('sysconfdir') / 'vintf' / 'manifest',
)
