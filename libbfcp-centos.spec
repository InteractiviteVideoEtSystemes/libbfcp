Name:      libbfcp
Version:   5.5.3
Release:   1.ives%{?dist}
Summary:   libbfcp.
Vendor:    IVeS
Group:     Library/Communication
License:   GPL V2 
URL:       https://github.com/neutrino38/libbfcp
BuildRoot:  %{_tmppath}/%{name}-%{version}-%{release}-root-%(%{__id_u} -n)
BuildArchitectures: i386, i586, x86_64

%description
An open source BFCP (Binary Floor Control Protocol, RFC4582) library written in C
and C++. Repackaged and modified for IVeS solutions. Fork from the libbfcp written
by Lorenzo Miniero (see Confiance open source project)

%clean
echo "############################# Clean"
echo Clean du repertoire $RPM_BUILD_ROOT
[ "$RPM_BUILD_ROOT" != "/" ] && rm -rf "$RPM_BUILD_ROOT"

%prep
cd %_topdir
cd ..


%build
echo "Build"
cd %_topdir
cd ..
make LIBSUBDIR=%{_lib}
make DEBUG=yes LIBSUBDIR=%{_lib}

%install
cd %_topdir
cd ..
make install PREFIXE=$RPM_BUILD_ROOT/opt/ives LIBSUBDIR=%{_lib}
make install DEBUG=yes PREFIXE=$RPM_BUILD_ROOT/opt/ives LIBSUBDIR=%{_lib}

%files
%defattr(-,root,root,-)
/opt/ives/%{_lib}/libbfcprel.so
/opt/ives/%{_lib}/libbfcpdbg.so
/opt/ives/%{_lib}/libbfcprel.a
/opt/ives/%{_lib}/libbfcpdbg.a
/opt/ives/include/
/opt/ives/doc/libbfcp
/opt/ives/bin/bfcpParticipant
/opt/ives/bin/bfcpServer

%changelog
* Mon Nov 2 2015 Emmanuel BUU <emmanuel.buu@ives.fr>
- implementation of BFCP over UDP 
* Mon Jan 20 2014 Philippe Verney <philippe.verney@ives.fr>
- libbfcp for linux and windows .
