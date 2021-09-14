project(
    'license-manager',
    'cpp',
    default_options: [
        'warning_level=3',
        'werror=true',
        'cpp_std=c++20'
    ],
    license: 'Apache-2.0',
    version: '0.1',
)


sdbusplus = dependency('sdbusplus')
sdeventplus = dependency('sdeventplus')
phosphorlogging = dependency('phosphor-logging')
phosphordbusinterfaces = dependency('phosphor-dbus-interfaces')

executable('license-manager',
            'mainapp.cpp',
            dependencies: [
            sdbusplus, sdeventplus, phosphorlogging,
            phosphordbusinterfaces
            ],
    implicit_include_directories: true,
    install: true
)

systemd = dependency('systemd')
systemd_system_unit_dir = systemd.get_pkgconfig_variable(
    'systemdsystemunitdir',
    define_variable: ['prefix', get_option('prefix')])

configure_file(
  copy: true,
  input: 'license-manager.service',
  install: true,
  install_dir: systemd_system_unit_dir,
  output: 'license-manager.service',
)
