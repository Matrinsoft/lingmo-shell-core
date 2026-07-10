%global majver 1
Name:          lingmo-shell-core
Version:       1.0.0
Release:       1%{?dist}
Summary:       Lingmo Desktop - Shell runtime core
License:       GPL-2.0-or-later
URL:           https://lingmo.org
Source0:       %{name}-%{version}.tar.gz
BuildRequires: cmake >= 3.21 ninja-build qt6-qtbase-devel
BuildRequires: lingmo-ipc-devel lingmo-utils-devel lingmo-config-devel
BuildRequires: lingmo-plugin-devel lingmo-theme-devel
%description
Shell runtime core that manages surfaces, plugins, and session integration
for the Lingmo Desktop environment.
%prep
%setup -q
%build
%cmake -G Ninja -DCMAKE_BUILD_TYPE=RelWithDebInfo -DBUILD_TESTING=OFF
%cmake_build
%install
%cmake_install
%package -n liblingmoshellcore%{majver}
Summary:        Runtime libraries for lingmo-shell-core

%description -n liblingmoshellcore%{majver}
Runtime libraries for lingmo-shell-core.

%package -n liblingmoshellcore-devel
Summary:        Development files for lingmo-shell-core
Requires:       liblingmoshellcore%{majver}%{?isa} = %{version}-%{release}

%description -n liblingmoshellcore-devel
Headers and CMake integration for building applications that use lingmo-shell-core.

%files -n liblingmoshellcore%{majver}
%license LICENSE
%{_libdir}/libLingmoShellCore.so.%{majver}*

%files -n liblingmoshellcore-devel
%{_includedir}/LingmoShellCore/
%{_libdir}/cmake/LingmoShellCore/
%{_libdir}/libLingmoShellCore.so

%files
%license LICENSE
%{_libexecdir}/lingmo-shell-core
%{_prefix}/lib/systemd/user/lingmo-shell-core.service
%{_prefix}/lib/systemd/user/lingmo-shell-core.target
%changelog
* Thu Jul 09 2026 Lingmo OS Team <team@lingmo.org> - 1.0.0-1
- Initial release
