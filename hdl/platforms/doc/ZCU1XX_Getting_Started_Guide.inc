\iffalse
This file is protected by Copyright. Please refer to the COPYRIGHT file
distributed with this source distribution.

This file is part of OpenCPI <http://www.opencpi.org>

OpenCPI is free software: you can redistribute it and/or modify it under the
terms of the GNU Lesser General Public License as published by the Free Software
Foundation, either version 3 of the License, or (at your option) any later
version.

OpenCPI is distributed in the hope that it will be useful, but WITHOUT ANY
WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A
PARTICULAR PURPOSE. See the GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License along
with this program. If not, see <http://www.gnu.org/licenses/>.
\fi
%----------------------------------------------------------------------------------------
% Update the docTitle and docVersion per document
%----------------------------------------------------------------------------------------
\def\docTitle{OpenCPI\\ \ZCUxxx{} Getting Started Guide}
\def\docVersion{1.4 - Geontech - Zynq UltraScale+ MPSoC/RFSoC Release}
%----------------------------------------------------------------------------------------
\input{../../../../snippets/LaTeX_Header.tex}
\date{Version \docVersion} % Force date to be blank and override date with version
\title{\docTitle}
\lhead{ \ZCUxxx{} Getting Started Guide}
%----------------------------------------------------------------------------------------
\usepackage[T1]{fontenc} % http://tex.stackexchange.com/a/181119
\usepackage{graphicx}
\graphicspath{ {figures/} }
\lstset{ % https://tex.stackexchange.com/a/116572
  basicstyle=\ttfamily,
  columns=fullflexible,
  % frame=single,
  breaklines=true,
  showstringspaces=true,
  showspaces=true,
  postbreak=\mbox{\textcolor{red}{$\hookrightarrow$}\space},
}
\begin{document}
\maketitle
\begin{figure}[H]
 \centering
 \includegraphics[scale=0.12]{figures/\zcuxxx_top_selections.jpg}
 \caption{Top View (\ZCUxxx{})}
 \label{fig:top}
\end{figure}
\newpage

\begin{center}
\textit{\textbf{Revision History}}
	\begin{table}[H]
	\label{table:revisions} % Add "[H]" to force placement of table
		\begin{tabularx}{\textwidth}{|c|X|l|}
		\hline
		\rowcolor{blue}
		\textbf{Revision} & \textbf{Description of Change} & \textbf{Date} \\
		\hline
	        release\_1.4\_zynq\_ultra (Geontech custom release) & Initial Release of Zynq UltraScale+ Support in branch off of OpenCPI's release\_1.4 & 1/2019 \\
		\hline
		\end{tabularx}
	\end{table}
\end{center}

\newpage

\tableofcontents

\newpage

\section{References}
	This document assumes a basic understanding of the Linux command line (or ``shell'') environment.  The reference(s) in Table 1 can be used as an overview of OpenCPI and may prove useful.

\def\refcapbottom{}
\input{../../../../snippets/References_Table}

\newpage
\section{Overview}
This document provides steps for configuring a factory provided Xilinx \ZCUxxx{} Evaluation Board with the OpenCPI runtime environment for executing applications, configuring a development system to build OpenCPI bitstreams targeting the \textit{\zcuxxx{}} platform, and examples of executing applications on the OpenCPI configured \ZCUxxx{}.

\section{Prerequisites}
\textbf{\textcolor{red}{WARNING:} OpenCPI development for the \ZCUxxx{} has only been verified using a CentOS7 development host.}
\begin{flushleft}
This guide assumes that, at a minimum, the following RPMs are installed:  \\
\begin{table}[H]
	\label{table:rpms}
		\begin{tabularx}{\textwidth}{|c|X|}
		\hline
		\rowcolor{blue}
		\textbf{RPM Name} & \textbf{Description} \\
		\hline
		\hline
		\path{opencpi-*1.4_zynq_ultra.x86_64.rpm} &
		Base installation RPM includes the runtime portion of the Component
Development Kit (CDK) and the source for the ocpi.core and ocpi.assets Projects containing framework essential components, workers,
platforms, etc. \\
		\hline
		\path{opencpi-devel-*1.4_zynq_ultra.x86_64.rpm} &
		Additional header files and scripts for developing new assets as HDL
and/or RCC. \\
		\hline
		\path{opencpi-sw-platform-xilinx18_2-*1.4_zynq_ultra.noarch.rpm} &
		Additional files necessary to build the framework targeting specific
RCC/software platforms, independent of the final deployed hardware. \\
		\hline
		\path{opencpi-hw-platform-}\texttt{\zcuxxx}\path{-*1.4_zynq_ultra.noarch.rpm} &
		Additional files necessary to build the framework targeting specific hard-ware platform "X" when running RCC platform "Y" ("Y" can be "no sw"). This RPM also includes hardware-specific SD Card images when applicable. \\
		\hline
	\end{tabularx}
\end{table}
There is an IDE developed by the ANGRYVIPER team which is generally used for a more graphical development process in OpenCPI, but \textbf{the IDE has never been tested with the \ZCUxxx{} BSP}. \footnote{Users wishing to use the IDE can following the instructions in Appendix B of ANGRYVIPER's \href{https://opencpi.github.io/RPM_Installation_Guide.pdf}{\textit{RPM\_Installation\_Guide}} revision 1.4.}\\\medskip

Initial support for the Zynq UltraScale+ MPSoC/RFSoC was done in a fork of OpenCPI within a branch off of OpenCPI's \code{release\_1.4}. So, the RPMs above must be acquired from Geon Technologies, LLC, and should have the label `\code{release\_1.4\_zynq\_ultra}' to denote the branch they were built from.\\\medskip

Note that the RFSoC is an architecture that builds on MPSoC by adding RF functionality. This OpenCPI release supports the Zynq UltraScale+ (on both the MPSoC and RFSoC devices), but \textbf{none of the RF capabilities of the RFSoC}.\\\medskip

Appendix~\ref{sec:oss-build} details the process for building from source and generating RPMs from source. Building RPMs from source is useful for users that do not have access to the RPM files. If the framework is built and installed from source, it is possible for experienced users to use this source installation \textit{instead} of an RPM installation. This is particularly useful for users who will need to make changes to the OpenCPI framework itself. If choosing to use a source-build installation, Section~\ref{sec:copy-projects} can be skipped, and Appendix~\ref{sec:oss-build} can be referenced for project creation/cloning and registration.

\subsection{Installation of required projects: \textit{core}, \textit{assets}, \textit{bsp\_zcu1xx} and \textit{sw\_xilinx18\_2}}
\label{sec:copy-projects}
If using a source-build of the OpenCPI framework, follow the instructions in Appendix~\ref{sec:src-clone} and skip this section.\\\medskip

If not completed already, the user must execute \textit{ocpi-copy-projects}, accepting the default settings, to copy and register the \textit{core} and \textit{assets} projects from the \path{/opt/opencpi/projects} to the user's workspace. Reference ANGRYVIPER's Getting Started Guide for details on \textit{ocpi-copy-projects}.  Although the projects are registered by \textit{ocpi-copy-projects}, changes to the registry can be made via \code{ocpidev un/register project}. An example of \textit{ocpi-copy-projects}' usage is below:\medskip

\begin{verbatim}
$ ocpi-copy-projects
...
$ ls ~/ocpi_projects
assets bsp_zcu1xx core sw_xilinx18_2
$ ocpidev show registry
Project registry is located at: /opt/opencpi/cdk/../project-registry
-----------------------------------------------------------------------------------------------
| Project Package-ID         | Path to Project                                 | Valid/Exists |
| ------------------         | ---------------                                 | ------------ |
| ocpi.assets                | /home/<user>/ocpi_projects/assets               | True         |
| ocpi.core                  | /home/<user>/ocpi_projects/core                 | True         |
-----------------------------------------------------------------------------------------------
\end{verbatim}

To build bitstreams and RCC workers for the \ZCUxxx{}, two other projects will need to be cloned and registered as well:
\begin{verbatim}
$ cd ~/ocpi_projects;
$ git clone https://github.com/Geontech/sw_xilinx18_2.git --branch release_1.4_zynq_ultra;
$ ocpidev register project sw_xilinx18_2;
$ git clone https://github.com/Geontech/bsp_zcu1xx.git    --branch release_1.4_zynq_ultra;
$ ocpidev register project bsp_zcu1xx;
$ ocpidev show registry
Project registry is located at: /opt/opencpi/cdk/../project-registry
-----------------------------------------------------------------------------------------------
| Project Package-ID         | Path to Project                                 | Valid/Exists |
| ------------------         | ---------------                                 | ------------ |
| ocpi.assets                | /home/<user>/ocpi_projects/assets               | True         |
| ocpi.core                  | /home/<user>/ocpi_projects/core                 | True         |
| com.geontech.bsp.zcu1xx    | /home/<user>/ocpi_projects/bsp_zcu1xx           | True         |
| com.geontech.sw.xilinx18_2 | /home/<user>/ocpi_projects/sw_xilinx18_2        | True         |
-----------------------------------------------------------------------------------------------
\end{verbatim}


\subsection{Vendor Software Setup}
The platform that is expected to be used is Xilinx's \ZCUxxx{} Evaluation Board (\textit{e.g.} \code{\zcuxxx{}}). This OpenCPI-enabled platform provides the capability of deploying hardware and software workers while using Xilinx's 2018.2 distribution of Linux.\\ \bigskip

\textbf{\textcolor{red}{IMPORTANT:} Use of OpenCPI on the \ZCUxxx{} requires Xilinx Vivado 2018.2 (including its SDK).}\\ \medskip
The synthesizers and cross-compilers required to build HDL and RCC Workers for the \ZCUxxx{} are present in Xilinx Vivado 2018.2. The instructions found in the \textit{OpenCPI FPGA Vendor Tools Installation Guide} detail the process for installing older versions of Vivado, but can be still be useful as they include details for installation options and processes. This document assumes that the user has installed the appropriate versions of Vivado and the Xilinx SDK.

\subsection{Building Required Projects}
\label{sec:Building OpenCPI projects}
The \textit{core}, \textit{assets} and \textit{bsp\_zcu1xx} projects must be built \textit{in a specific order} for this platform. This section outlines how to build the relevant projects and provides the commands to do so.\medskip

For this document, the projects should be built as follows:\\

\begin{enumerate}
	\item Build \code{core} for the \code{xilinx18\_2} RCC Platform and the \code{\zcuxxx{}} HDL Platform, but omit assemblies
	\item Build \code{assets} for the \code{xilinx18\_2} RCC Platform and the \code{\zcuxxx{}} HDL Platform, but omit assemblies
	\item Build the \code{bsp\_zcu1xx} project for these same platforms
	\item Build the \code{testbias} assembly from the \code{assets} project. This will be used later in this guide.
		\subitem Once the HDL Platform is built in the BSP project, assemblies can be built for that HDL platform
\end{enumerate}
\texttt{\\
\$ cd /home/<user>/ocpi\_projects/;\\
\$ ocpidev build -d core~~~~~~~-{}-rcc-platform xilinx18\_2~-{}-hdl-platform \zcuxxx{} -{}-no-assemblies;\\
\$ ocpidev build -d assets~~~~~-{}-rcc-platform xilinx18\_2~-{}-hdl-platform \zcuxxx{} -{}-no-assemblies;\\
\$ ocpidev build -d bsp\_zcu1xx~-{}-rcc-platform xilinx18\_2~-{}-hdl-platform \zcuxxx{};\\
\$ ocpidev build -d assets hdl assembly testbias~~~~~~~~~-{}-hdl-platform \zcuxxx{};\\
}
Note: replace ``\code{<user>}'' with your username in the commands above.\\\medskip

See the ANGRYVIPER Team's Getting Started Guide for additional information concerning the use of \code{ocpidev} to build OpenCPI assets.

\subsection{Hardware Setup and Requirements}
\begin{itemize}
\item \textbf{Xilinx \ZCUxxx{} Evaluation Board}\\ \medskip
It is expected that this evaluation kit includes a power supply, micro-USB to USB cable and a micro SD card (4GB or larger). \\ \medskip
The micro-USB serial port on the \ZCUxxx{} labeled \uart (Figure~\ref{fig:top}) can be used to access the serial connection with the processor.\medskip

\item \textbf{Board Switch Settings}\\ \medskip
As mentioned in Table 2-4 of Xilinx's UG1271, set SW6 to 1110 for SD card boot mode. This means that the SW6's switch labeled 1 is `ON' and 2, 3, and 4 are `OFF'. See Figure~\ref{fig:top}.
\item \textbf{Ethernet cable}:
An Ethernet port is available on the \ZCUxxx{} (Figure~\ref{fig:top}) and is required when the Network mode (discussed later) environment is used. The OpenCPI BSP for the \ZCUxxx{} is configured for DHCP.\medskip

\item \textbf{Access to a network which supports DHCP. (Network Mode)}

\item \textbf{SD card}:
As mentioned earlier, a 4GB or larger micro SD card should come with the board. The bootable SD card slot is located on the front of the unit (Figure~\ref{fig:top}) and ejects by gently pushing it in and releasing.

\item \textbf{SD card reader}

\end{itemize}
\end{flushleft}

\section{SD Card Setup}
\label{sec:SD_Card_Setup}
\subsection{Make a backup image of factory SD card (assumes Linux host)}
This section provides the steps for creating an SD card backup image. The subsequent subsections assume the SD card is empty.

\begin{itemize}
\item Determine the device file name for the SD card by executing dmesg command below. It will likely be something like \texttt{/dev/sdb} or \texttt{/dev/mmcblk0}.\\
\texttt{\$ dmesg | tail -n 15} \\
\item Run the following dd command to make a backup image, where DEVICENAME was determined above. This step should take $\sim15$ minutes depending on the card size.\\ \medskip
\texttt{\$ dd if=DEVICENAME of=backup.image}
\end{itemize}
\noindent To restore the card back to the original contents, run the command ``\texttt{dd of=DEVICENAME if=backup.image}'' (Do not do this step unless you want the original contents back on the SD card.)

\subsection{Generate the SD card image}
\label{sec:sdgen}
This section describes how to use Yocto to generate a Xilinx 18.2 SD card image for OpenCPI. If you already have an OpenCPI SD card image (\code{opencpi-runtime-image-\zcuxxx{}-zynqmp.wic}) for the \ZCUxxx{}, you can move on to the next section.
\begin{enumerate}
\item Follow instructions at \url{https://www.yoctoproject.org/docs/2.0/yocto-project-qs/yocto-project-qs.html} to install Yocto's prerequisite RPMs
\item Follow the  ``Downloading'', ``Setup'' and ``Build'' instructions at \url{https://github.com/Geontech/opencpi-manifest.git} to perform the following:
\begin{enumerate}
\item \underline{Downloading}: clone all of the required Yocto layers and projects for use of Xilinx's 2018.2 distribution Linux with OpenCPI
\item \underline{Setup}: setup the environment
\begin{enumerate}
\item Copy OpenCPI's \ZCUxxx{} SD card files over to the \code{meta-opencpi} layer (from OpenCPI installation - details in Appendix~\ref{sec:oss-build})
\item Setup the environment for \code{bitbake}
\end{enumerate}
\item \underline{Building}: Build the \code{opencpi-runtime-image} using \code{bitbake}
\end{enumerate}
\end{enumerate}

You should now be in the \code{build/} directory, and from there the SD card image can be found at:\\
\indent\indent\code{tmp/deploy/images/\zcuxxx{}-zynqmp/opencpi-runtime-image-\zcuxxx{}-zynqmp.wic}
\subsection{Write image to SD card}
This section is also covered in the \code{opencpi-manifest} mentioned above at \url{https://github.com/Geontech/opencpi-manifest.git}, but it is summarized here for convenience.
\begin{itemize}
\item Determine the device file name for the SD card by executing dmesg command below. It will likely be something like \texttt{/dev/sdb} or \texttt{/dev/mmcblk0}.\\
\texttt{\$ dmesg | tail -n 15} \\
\item Write \code{opencpi-runtime-image-\zcuxxx{}-zynqmp.wic} to the SD card, replacing $<SD card device file name>$ with the device file name determined in the previous step and ensuring that the path to the \code{wic} file is valid:\\
\texttt{\\
\$ sudo dd if=<path-to>/opencpi-runtime-image-\zcuxxx-zynqmp.wic \textbackslash\\
    \indent of=<SD-card-device-file-name> bs=1M \&\& sync;
}
\end{itemize}

\section{Script Setup}
There are two type of setups or modes for running applications on any embedded radio: Network and Standalone. In Network mode, a development system hosts the OpenCPI tree as an NFS server to the \ZCUxxx{} which is an NFS client. This configuration provides quick and dynamic access to all of OpenCPI, and presumably any applications, components and bitstreams. In Standalone mode, all the artifacts are located on the board's local storage (\textit{e.g.} SD card) and no network connection is required. This may be more suited for \textit{deployment} scenarios in which network connection is not possible or practical. Network mode is generally preferred during the development process.\\

\noindent For both Network and Standalone mode, the following step is necessary:\\\\
1) Unplug the SD card from the host and plug it back in so its contents are mounted\\

\noindent Note: any commands creating or editing files on the SD card from the host will require use of ``\code{sudo}''. As an alternative, many of these file changes can actually be made on the \ZCUxxx{} itself after booting the board.

\begin{flushleft}

\subsection{Setting up the Network and Standalone Mode scripts}

For each mode, a startup script is used to configure the environment of the embedded system. The OpenCPI framework provides a default script for each mode. The default scripts are to be copied and then modified per the user's requirements.\par\medskip

\subsubsection{Network Mode}
1) Make a copy of the default script for editing (the name of the script ``\path{mynetsetup.sh}'' is important for proper execution):
\begin{verbatim}
$ cp /run/media/<user>/root/home/root/opencpi/default_mynetsetup.sh \
     /run/media/<user>/root/home/root/opencpi/mynetsetup.sh;
\end{verbatim}\medskip

2) Edit the copy
\begin{enumerate}
\item In \texttt{mynetsetup.sh}, uncomment the following lines which are necessary for mounting \textit{core}, \textit{assets}, and \textit{bsp\_zcu1xx} projects:

\begin{verbatim}
mkdir -p /mnt/ocpi_core
mount -t nfs -o udp,nolock,soft,intr $1:/home/<user>/ocpi_projects/core /mnt/ocpi_core
mkdir -p /mnt/ocpi_assets
mount -t nfs -o udp,nolock,soft,intr $1:/home/<user>/ocpi_projects/assets /mnt/ocpi_assets
mkdir -p /mnt/bsp_zcu1xx
mount -t nfs -o udp,nolock,soft,intr $1:/home/<user>/ocpi_projects/bsp_zcu1xx /mnt/bsp_zcu1xx
\end{verbatim}
 \item Edit \texttt{/home/<user>/ocpi\_projects/core} and \texttt{/home/<user>/ocpi\_projects/assets} to reflect the paths to the \textit{core}, \textit{assets}, and \textit{bsp\_zcu1xx} projects on the host, for example:
\begin{verbatim}
mkdir -p /mnt/ocpi_core
mount -t nfs -o udp,nolock,soft,intr $1:/home/johndoe/ocpi_projects/core /mnt/ocpi_core
mkdir -p /mnt/ocpi_assets
mount -t nfs -o udp,nolock,soft,intr $1:/home/johndoe/ocpi_projects/assets /mnt/ocpi_assets
mkdir -p /mnt/bsp_zcu1xx
mount -t nfs -o udp,nolock,soft,intr $1:/home/johndoe/ocpi_projects/bsp_zcu1xx /mnt/bsp_zcu1xx
\end{verbatim}
\end{enumerate}

\subsubsection{Standalone Mode}
	In this mode, all OpenCPI artifacts that are required to run any application on the \ZCUxxx{} must be copied onto the SD card.  Building the provided projects to obtain such artifacts is discussed in Section~\ref{sec:Building OpenCPI projects}. Once the artifacts have been created, they must be copied to the SD card (\textit{e.g.} \path{/run/media/<user>/root/home/root/opencpi/} or a new subdirectory there called \path{artifacts}) In general, any required \texttt{.so} (RCC workers), \texttt{.bin.gz} (hdl assemblies), and application XMLs or executables must be copied to the SD card.\medskip

1) Make a copy of the default script for editing (the name of the script ``\path{mysetup.sh}'' is important for proper execution):
\begin{verbatim}
$ cp /run/media/<user>/root/home/root/opencpi/default_mysetup.sh \
     /run/media/<user>/root/home/root/opencpi/mysetup.sh;
\end{verbatim}\medskip

2) Edit the copy\\ \medskip
Unlike Network mode, there is no required modifications to this script. \medskip

3) Copy any additional artifacts (\textit{i.e.} \code{*bin.gz} or \code{*.so} files) to SD card's \path{opencpi/artifacts/} directory \medskip

\end{flushleft}

\pagebreak
\section{Development Host Setup - for Network Mode ONLY}
\textbf{\textcolor{red}{WARNING:} The \ZCUxxx{} in OpenCPI network mode has only been tested using a CentOS7 development host.}

% Bring in NFS setup snippet (has subsections)
\input{../../../../snippets/NFS_Setup_Snippet.tex}
%
\\\\Note: You will need to add the \code{com.geontech.bsp.zcu1xx} (directory name \path{bsp_zcu1xx}) project to your list of exports (in \path{/etc/exports.d/user_ocpi.exports}).

\pagebreak
\section{Configuring the runtime environment on the platform}
This section details the runtime environment configuration steps for Network and Standalone modes on the \ZCUxxx. Note that if you wish to switch from one mode to the other, run the following command on the \ZCUxxx{} and reboot:
\begin{verbatim}
$ rm /home/root/.profile;
\end{verbatim}
\subsection{Network Mode}
\begin{enumerate}
\item Plug in an Ethernet cable to a network configured for DHCP
\item Ensure a micro-USB to USB cable is connected between the \ZCUxxx{}'s serial port and development host
\item Apply power to the \ZCUxxx{}
\item Use a serial terminal application to establish a serial connection, for example:

\tty
\item After a successful boot to PetaLinux, login to the system, using  ``\textbf{root}'' for user name and password

\item Setup the OpenCPI environment on remote system

\begin{flushleft}
Each time the board is booted, the OpenCPI environment must be setup. By sourcing the \texttt{mynetsetup.sh} script, the remote system's environment is configured for OpenCPI and NFS directories are mounted for Network mode.\footnote{This script calls the \texttt{zynqmp\_net\_setup.sh} script, which should not be modifiable by the user.}. The user must provide the network address of the development system to the script as its only argument:
\begin{verbatim}
$ . /home/root/opencpi/mynetsetup.sh XX.XX.XX.XX
\end{verbatim}

where XX.XX.XX.XX is the IP address of the NFS host (i.e. that development host, \textit{e.g.} 192.168.1.10). A successful run should output the following:
\begin{verbatim}
An IP address was detected.
My IP address is: 10.3.1.103, and my hostname is: zcu<xxx>-zynqmp
Running login script. OCPI_CDK_DIR is now /mnt/net/cdk.
Executing /etc/profile.d/opencpi-persist.sh
No /etc/opencpi-release - assuming xilinx18_2 hardware
No reserved DMA memory found on the linux boot command line.
[   80.700634] opencpi: loading out-of-tree module taints kernel.
[   80.707133] opencpi: dmam_alloc_coherent failed
[   80.711608] opencpi: get_dma_memory failed in opencpi_init, trying fallback
[   80.718552] opencpi: dmam_alloc_coherent failed
[   80.723038] opencpi: get_dma_memory in request_memory failed, trying fallback
[   80.730156] opencpi: if allocation failure occurs, see README for memmap configuration
[   80.738074] NET: Registered protocol family 12
Driver loaded successfully.
OpenCPI ready for zynq_ultra.
Discovering available containers...
OCPI( 2:527.0378): HDL Device 'PL:0' responds, but the OCCP signature: magic: 0xffffffff00000000 (sb 0x435049004f70656e)
Available containers:
 #  Model Platform       OS     OS-Version  Arch     Name
 0  hdl   zcu<xxx>                                   PL:0
 1  rcc   xilinx18_2     linux  x18_2       arm64    rcc0
\end{verbatim}
Note: The line in this output regarding the OCCP signature is printed because the default bitstream on the board is not an OpenCPI one. Once an OpenCPI bitstream is loaded on the board, \code{ocpirun -C} will not include this output.
\end{flushleft}
\end{enumerate}

\pagebreak
\subsection{Standalone Mode}
\begin{enumerate}
\item (Not required for this mode - see Item~\ref{item:nonet-ip}) Plug in an Ethernet cable to a network configured for DHCP
\item Ensure a micro-USB to USB cable is connected between the \ZCUxxx{}'s serial port and development host
\item Apply power to the \ZCUxxx{}
\item Use a serial terminal application to establish a serial connection, for example:

\tty

\item After a successful boot to PetaLinux, login to the system, using  ``\textbf{root}'' for user name and password

\item \label{item:nonet-ip}\textcolor{red}{WARNING:}
Applications (including XML-only ones) fail if there is not an IP address assigned to the platform, even when in ``standalone mode.'' When the Ethernet port is not connected to a network configured with DHCP, a temporary IP address must be set:
\begin{verbatim}
$ ifconfig eth0 192.168.244.244
\end{verbatim} \medskip

\item Setup the OpenCPI environment on remote system

\begin{flushleft}
Each time the board is booted, the OpenCPI environment must be setup. By sourcing the \texttt{mysetup.sh} script, the remote system's environment is configured for OpenCPI \footnote{This script calls the \texttt{zynqmp\_setup.sh} script, which should not be modifiable by the user.}. There are no arguments for this script.
\begin{verbatim}
$ . /home/root/opencpi/mysetup.sh
\end{verbatim}

A successful run should output the following:
\begin{verbatim}
Running login script. OCPI_CDK_DIR is now /home/root/opencpi.
Executing /home/root/.profile
No reserved DMA memory found on the linux boot command line.
The mdev config has no OpenCPI rules. We will add them to /etc/mdev.conf
NET: Registered protocol family 12
Driver loaded successfully.
OpenCPI ready for zynq_ultra.
Discovering available containers...
Available containers:
 #  Model Platform       OS     OS-Version  Arch     Name
 0  hdl   zcu<xxx>                                   PL:0
 1  rcc   xilinx18_2     linux  x13_4       arm      rcc0
\end{verbatim}
\end{flushleft}
\end{enumerate}

\pagebreak
\section{Build an Application}
\begin{flushleft}
The setup of the platform can be verified by running an application that uses both RCC and HDL workers. A simple application that requires two RCC and one HDL worker is located in \texttt{assets/applications/bias.xml}, but only the RCC artifacts are provided with the installation of RPMs, and are availble on the SD card (Standard Mode) or mounted CDK directory (Network Mode). The remaining task is to build an assembly, or bitstream for loading the FPGA, which contains the HDL worker.
\end{flushleft}

\section{Run an Application}
\subsection{Network Mode}
 \label{sec:ocpirun_net}
The default setup script sets the \texttt{OCPI\_LIBRARY\_PATH} variable to include the RCC workers that are required to execute the application, but it must be updated to include to the assembly bitstream that was built.  After running the \texttt{mynetsetup.sh} script, navigate to  \texttt{/mnt/ocpi\_assets/applications}, then update the \texttt{OCPI\_LIBRARY\_PATH} variable using the following command:
\begin{verbatim}
$ export OCPI_LIBRARY_PATH=/mnt/ocpi_assets/artifacts:/mnt/ocpi_core/artifacts
\end{verbatim}
Run the application using the following command:
\begin{verbatim}
$ ocpirun -v -d -m bias=hdl bias.xml
\end{verbatim}
The output should be similar to:
\begin{lstlisting}[showspaces=false]
Available containers are:  0: PL:0 [model: hdl os:  platform: zcu<xxx>], 1: rcc0 [model: rcc os: linux platform: xilinx18_2]
Actual deployment is:[  980.856510] opencpi: dmam_alloc_coherent failed
  Instance  0 file_read (spec ocpi.core.file_read) on rcc container 1: rcc0, using file_read in /mnt/net/projects/core/artifacts/ocpi.core.file_read.rcc.0.xilinx18_2.so dated Fri Jan 18 16:22:34 2019
[  980.862362] opencpi: get_dma_memory in request_memory failed, trying fallback
[  980.875023] opencpi: if allocation failure occurs, see README for memmap configuration
  Instance  1 bias (spec ocpi.core.bias) on hdl container 0: PL:0, using bias_vhdl/a/bias_vhdl in /mnt/net/projects/assets/artifacts/ocpi.assets.testbias_zcu<xxx>_base.hdl.0.zcu<xxx>.gz dated Mon Jan 28 11:40:53 2019
  Instance  2 file_write (spec ocpi.core.file_write) on rcc container 1: rcc0, using file_write in /mnt/net/projects/core/artifacts/ocpi.core.file_write.rcc.0.xilinx18_2.so dated Fri Jan 18 16:22:39 2019
Application XML parsed and deployments (containers and artifacts) chosen
Application established: containers, workers, connections all created
Communication with the application established
Dump of all initial property values:
Property  0: file_read.fileName = "test.input" (cached)
Property  1: file_read.messagesInFile = "false" (cached)
Property  2: file_read.opcode = "0" (cached)
Property  3: file_read.messageSize = "16"
Property  4: file_read.granularity = "4" (cached)
Property  5: file_read.repeat = "<unreadable>"
Property  6: file_read.bytesRead = "0"
Property  7: file_read.messagesWritten = "0"
Property  8: file_read.suppressEOF = "false"
Property  9: file_read.badMessage = "false"
Property 10: file_read.ocpi_debug = "false" (parameter)
Property 11: file_read.ocpi_endian = "little" (parameter)
Property 12: bias.biasValue = "16909060" (cached)
Property 13: bias.ocpi_debug = "false" (parameter)
Property 14: bias.ocpi_endian = "little" (parameter)
Property 15: bias.test64 = "0"
Property 16: file_write.fileName = "test.output" (cached)
Property 17: file_write.messagesInFile = "false" (cached)
Property 18: file_write.bytesWritten = "0"
Property 19: file_write.messagesWritten = "0"
Property 20: file_write.stopOnEOF = "true" (cached)
Property 21: file_write.ocpi_debug = "false" (parameter)
Property 22: file_write.ocpi_endian = "little" (parameter)
Application started/running
Waiting for application to finish (no time limit)
Application finished
Dump of all final property values:
Property  3: file_read.messageSize = "16"
Property  5: file_read.repeat = "<unreadable>"
Property  6: file_read.bytesRead = "4000"
Property  7: file_read.messagesWritten = "251"
Property  8: file_read.suppressEOF = "false"
Property  9: file_read.badMessage = "false"
Property 15: bias.test64 = "0"
Property 18: file_write.bytesWritten = "4000"
Property 19: file_write.messagesWritten = "250"
\end{lstlisting}

\noindent Run the following command to view the input:
\begin{verbatim}
$ hexdump test.input | less
\end{verbatim}
 The output should look like the following:
\begin{verbatim}
0000000 0000 0000 0001 0000 0002 0000 0003 0000
0000010 0004 0000 0005 0000 0006 0000 0007 0000
0000020 0008 0000 0009 0000 000a 0000 000b 0000
0000030 000c 0000 000d 0000 000e 0000 000f 0000
0000040 0010 0000 0011 0000 0012 0000 0013 0000
0000050 0014 0000 0015 0000 0016 0000 0017 0000
0000060 0018 0000 0019 0000 001a 0000 001b 0000
0000070 001c 0000 001d 0000 001e 0000 001f 0000
0000080 0020 0000 0021 0000 0022 0000 0023 0000
0000090 0024 0000 0025 0000 0026 0000 0027 0000
00000a0 0028 0000 0029 0000 002a 0000 002b 0000
00000b0 002c 0000 002d 0000 002e 0000 002f 0000
00000c0 0030 0000 0031 0000 0032 0000 0033 0000
00000d0 0034 0000 0035 0000 0036 0000 0037 0000
00000e0 0038 0000 0039 0000 003a 0000 003b 0000
00000f0 003c 0000 003d 0000 003e 0000 003f 0000
0000100 0040 0000 0041 0000 0042 0000 0043 0000
0000110 0044 0000 0045 0000 0046 0000 0047 0000
0000120 0048 0000 0049 0000 004a 0000 004b 0000
0000130 004c 0000 004d 0000 004e 0000 004f 0000
0000140 0050 0000 0051 0000 0052 0000 0053 0000
0000150 0054 0000 0055 0000 0056 0000 0057 0000
0000160 0058 0000 0059 0000 005a 0000 005b 0000
\end{verbatim}

\noindent Run the following command to view the output: \\
\begin{verbatim}
$ hexdump test.output | less
\end{verbatim}\medskip
 The output should look like the following:
\begin{verbatim}
0000000 0304 0102 0305 0102 0306 0102 0307 0102
0000010 0308 0102 0309 0102 030a 0102 030b 0102
0000020 030c 0102 030d 0102 030e 0102 030f 0102
0000030 0310 0102 0311 0102 0312 0102 0313 0102
0000040 0314 0102 0315 0102 0316 0102 0317 0102
0000050 0318 0102 0319 0102 031a 0102 031b 0102
0000060 031c 0102 031d 0102 031e 0102 031f 0102
0000070 0320 0102 0321 0102 0322 0102 0323 0102
0000080 0324 0102 0325 0102 0326 0102 0327 0102
0000090 0328 0102 0329 0102 032a 0102 032b 0102
00000a0 032c 0102 032d 0102 032e 0102 032f 0102
00000b0 0330 0102 0331 0102 0332 0102 0333 0102
00000c0 0334 0102 0335 0102 0336 0102 0337 0102
00000d0 0338 0102 0339 0102 033a 0102 033b 0102
00000e0 033c 0102 033d 0102 033e 0102 033f 0102
00000f0 0340 0102 0341 0102 0342 0102 0343 0102
0000100 0344 0102 0345 0102 0346 0102 0347 0102
0000110 0348 0102 0349 0102 034a 0102 034b 0102
0000120 034c 0102 034d 0102 034e 0102 034f 0102
0000130 0350 0102 0351 0102 0352 0102 0353 0102
0000140 0354 0102 0355 0102 0356 0102 0357 0102
0000150 0358 0102 0359 0102 035a 0102 035b 0102
0000160 035c 0102 035d 0102 035e 0102 035f 0102
\end{verbatim}

\newpage
\subsection{Run an Application in Standalone Mode}
\begin{flushleft}
The default setup script sets the \texttt{OCPI\_LIBRARY\_PATH} variable to include the all of the artifacts that are required to execute the application. Specifically, all three of the artifacts that are located on the SD card are mounted at \texttt{/home/root/opencpi/xilinx18\_2/artifacts}.  After running \texttt{mysetup.sh}, navigate to \texttt{/home/root/opencpi/xml}.

Run the application using the following command:
\begin{verbatim}
$ ocpirun -v -d -m bias=hdl bias.xml
\end{verbatim}
The output should be similar to the output shown in Section~\ref{sec:ocpirun_net}.
\end{flushleft}

\noindent Run the following commands to view the input and output, and reference Section~\ref{sec:ocpirun_net} for the expected results: \\
\begin{verbatim}
$ hexdump test.input | less
\end{verbatim}
\begin{verbatim}
$ hexdump test.output | less
\end{verbatim}

\section{Running Reference Applications}
Now that you have set up OpenCPI and the \ZCUxxx{} board, you can run the FSK reference application found in \code{assets/applications} in its testbench/file-read-write mode. This assumes that the build commands in Section~\ref{sec:Building OpenCPI projects} were run successfully.\\

\noindent To build the \code{fsk\_filerw} assembly and \code{FSK} application, run the following from the host:
\texttt{\\
\$ ocpidev build hdl assembly fsk\_filerw -{}-hdl-platform \zcuxxx;\\
\$ ocpidev build application FSK -{}-rcc-platform xilinx18\_2;
}
To run the application on the \ZCUxxx{}, the \code{OCPI\_LIBRARY\_PATH} must first be set to point to all build artifacts needed for this application.  For more information regarding the required \code{OCPI\_LIBRARY\_PATH} and other runtime requirements, reference the \textit{FSK\_App\_Getting\_Started\_Guide.pdf} and \textit{FSK\_app.pdf} documents. The application can be run \code{filerw} mode on the \ZCUxxx{}:
\begin{lstlisting}[showspaces=false]
$ ./target-xilinx18_2/FSK filerw
\end{lstlisting}
\newpage

\begin{appendices}
\section{Building OpenCPI, its RPMs and \ZCUxxx{} SD card contents from source}
\label{sec:oss-build}
\subsection{Building OpenCPI for centos7 and xilinx18\_2 cross-compilation}
In order to build the framework from source, you must first clone Geontech's OpenCPI fork and checkout the \code{release\_1.4\_zynq\_ultra} branch:
\begin{lstlisting}[showspaces=false]
$ git clone https://github.com/Geontech/opencpi.git --branch release_1.4_zynq_ultra;
\end{lstlisting}

\noindent Next, enter the OpenCPI repository and install the framework for the \code{centos7} host (make sure you have no \code{OCPI\_*} environment variables set before this step):
\begin{lstlisting}[showspaces=false]
$ cd opencpi;
$ unset OCPI_PREREQUISITES_DIR OCPI_CDK_DIR OCPI_TOOL_DIR OCPI_TOOL_ARCH OCPI_TOOL_PLATFORM \
         OCPI_TOOL_OS OCPI_TOOL_OS_VERSION OCPI_TOOL_PLATFORM_DIR;
$ ./scripts/install-opencpi.sh;
\end{lstlisting}
Set up your environment (this can optionally be added to your \path{~/.bashrc}):
\begin{lstlisting}[showspaces=false]
$ source ./cdk/opencpi-setup.sh -r;
\end{lstlisting}
This will set various environment variables such as \code{OCPI\_CDK\_DIR}.\\

\subsection{Cloning and registering BSP and SW projects within the source repository}
\label{sec:src-clone}
\noindent Next, you must clone the \code{bsp\_zcu1xx} and \code{sw\_xilinx18\_2} repositories into OpenCPI's \code{projects/bsps/} directory and register them:
\begin{verbatim}
$ cd projects/bsps;
$ git clone https://github.com/Geontech/sw_xilinx18_2.git --branch release_1.4_zynq_ultra;
$ ocpidev register project sw_xilinx18_2;
$ git clone https://github.com/Geontech/bsp_zcu1xx.git    --branch release_1.4_zynq_ultra;
$ ocpidev register project bsp_zcu1xx;
$ ocpidev show registry;
Project registry is located at: <path-to>/opencpi/cdk/../project-registry
---------------------------------------------------------------------------------------------
| Project Package-ID         | Path to Project                               | Valid/Exists |
| ------------------         | ---------------                               | ------------ |
| ocpi.assets                | <path-to>/opencpi/projects/assets             | True         |
| ocpi.core                  | <path-to>/opencpi/projects/core               | True         |
| com.geontech.bsp.zcu1xx    | <path-to>/opencpi/projects/bsps/bsp_zcu1xx    | True         |
| com.geontech.sw.xilinx18_2 | <path-to>/opencpi/projects/bsps/sw_xilinx18_2 | True         |
---------------------------------------------------------------------------------------------
$ cd -; # return to top level
\end{verbatim}

\subsection{Building OpenCPI for xilinx18\_2 cross-compilation}
\noindent Run the following to build and install the framework for \code{xilinx18\_2} cross-compilation:
\begin{verbatim}
$ ./scripts/install-opencpi.sh xilinx18_2;
\end{verbatim}

\subsection{Populate the SD card directory for the \ZCUxxx{}}
After building the framework for cross-compilation with \code{xilinx18\_2}, the \ZCUxxx{} SD card contents can be staged for deployment:\\
\texttt{\\
\$ make deploy Platform=xilinx18\_2;\\
\$ make Platform=\zcuxxx{};\\
\$ make deploy Platform=\zcuxxx{};
}\\
Note: it is okay if some ``\code{mv}'' or ``\code{rmdir}'' commands fail towards the end of ``\code{make deploy}'' involving the ``\path{tmp}'' directory.\\

\noindent There should now be a directory called \code{cdk/\zcuxxx{}/\zcuxxx{}-deploy/sdcard-xilinx18\_2/opencpi} which is the directory to copy over to the ``\code{meta-opencpi}'' layer (or just SD card root partition's \path{/home/root/}) in the steps in Section~\ref{sec:sdgen}.

\subsection{Generate RPMs (\code{centos7}, \code{xilinx18\_2} and \code{\zcuxxx{}})}
If you wish to generate RPMs with this OpenCPI installation packaged up, the following commands will generate the necessary RPMs:\\
\texttt{\\
\$ make rpm;\\
\$ make rpm Platform=xilinx18\_2;\\
\$ make rpm Platform=\zcuxxx{};
}\\

\noindent RPMs can now be found in \path{packages/target-*} for each target platform (\code{centos7}, \code{xilinx18\_2} and \code{\zcuxxx{}}).

\end{appendices}

\end{document}
