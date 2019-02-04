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
\documentclass{article}

\author{} % Force author to be blank
%----------------------------------------------------------------------------------------
% Paper size, orientation and margins
%----------------------------------------------------------------------------------------
\usepackage{geometry}
\geometry{
	letterpaper,			% paper type
	portrait,				% text direction
	left=.75in,				% left margin
	top=.75in,				% top margin
	right=.75in,			% right margin
	bottom=.75in			% bottom margin
 }
%----------------------------------------------------------------------------------------
% Header/Footer
%----------------------------------------------------------------------------------------
\usepackage{fancyhdr} \pagestyle{fancy} % required for fancy headers
\usepackage{multirow}
\usepackage{longtable}
\renewcommand{\headrulewidth}{0.5pt}
\renewcommand{\footrulewidth}{0.5pt}
\rhead{\small{Geon Technologies, LLC}}
%----------------------------------------------------------------------------------------
% Appendix packages
%----------------------------------------------------------------------------------------
\usepackage[toc,page]{appendix}
%----------------------------------------------------------------------------------------
% Defined Commands & Renamed Commands
%----------------------------------------------------------------------------------------
\renewcommand{\contentsname}{Table of Contents}
\renewcommand{\listfigurename}{List of Figures}
\renewcommand{\listtablename}{List of Tables}
\newcommand{\todo}[1]{\textcolor{red}{TODO: #1}\PackageWarning{TODO:}{#1}} % To do notes
\newcommand{\code}[1]{\texttt{#1}} % For inline code snippet or command line
%----------------------------------------------------------------------------------------
% Various pacakges
%----------------------------------------------------------------------------------------
\usepackage{hyperref} % for linking urls and lists
\usepackage{graphicx} % for including pictures by file
\usepackage{listings} % for coding language styles
\usepackage{rotating} % for sideways table
\usepackage{pifont}   % for sideways table
\usepackage{pdflscape} % for landscape view
%----------------------------------------------------------------------------------------
% Table packages
%----------------------------------------------------------------------------------------
\usepackage{longtable} % for long possibly multi-page tables
\usepackage{tabularx} % c=center,l=left,r=right,X=fill
\usepackage{float}
\floatstyle{plaintop}
\usepackage[tableposition=top]{caption}
\newcolumntype{P}[1]{>{\centering\arraybackslash}p{#1}}
\newcolumntype{M}[1]{>{\centering\arraybackslash}m{#1}}
%----------------------------------------------------------------------------------------
% Block Diagram / FSM Drawings
%----------------------------------------------------------------------------------------
\usepackage{tikz}
\usetikzlibrary{shapes,arrows,fit,positioning}
\usetikzlibrary{automata} % used for the fsm
\usetikzlibrary{calc} % For duplicating clients
\usepgfmodule{oo} % To define a client box
%----------------------------------------------------------------------------------------
% Colors Used
%----------------------------------------------------------------------------------------
\usepackage{colortbl}
\definecolor{blue}{rgb}{.7,.8,.9}
\definecolor{ceruleanblue}{rgb}{0.16, 0.32, 0.75}
\definecolor{drkgreen}{rgb}{0,0.6,0}
\definecolor{deepmagenta}{rgb}{0.8, 0.0, 0.8}
\definecolor{cyan}{rgb}{0.0,0.6,0.6}
\definecolor{maroon}{rgb}{0.5,0,0}
%----------------------------------------------------------------------------------------
% Update the docTitle and docVersion per document
%----------------------------------------------------------------------------------------
\def\docTitle{Platform Data Sheet}
\def\docVersion{release\_1.4\_zynq\_ultra}
%----------------------------------------------------------------------------------------
\date{Version \docVersion} % Force date to be blank and override date with version
\title{\docTitle}
\lhead{\small{\docTitle}}

\def\comp{\zcuxxx{}}
\edef\ecomp{\zcuxxx{}}
\def\Comp{\ZCUxxx{} Platform}
\graphicspath{ {figures/} }

\begin{document}

\section*{Summary - \Comp}
\textcolor{red}{This is a preliminary release of this document}\\
\begin{tabular}{|c|M{6cm}|}
	\hline
	\rowcolor{blue}
	                  &                                                    \\
	\hline
	Name              & \comp                                              \\
	\hline
	Worker Type       & Platform                                           \\
	\hline
	Latest Supported OpenCPI Version & release\_1.4\_zynq\_ultra \color{red} custom version \\%v1.4 \cite{github_opencpi_v1p4} \\
	\hline
	Supported Vendor Toolset/Version & Vivado 2018.2 + SDK \\
	\hline
	Component Library & com.geontech.bsp.zcu1xx                                   \\
	\hline
	Workers & \comp                                        \\
	\hline
\end{tabular}

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

\section{Block Diagrams}
\subsection{Top level}
\makeatletter
\newcommand{\gettikzxy}[3]{%
  \tikz@scan@one@point\pgfutil@firstofone#1\relax
  \edef#2{\the\pgf@x}%
  \edef#3{\the\pgf@y}%
}
\makeatother
\pgfooclass{clientbox}{ % This is the class clientbox
    \method clientbox() { % The clientbox
    }
    \method apply(#1,#2,#3,#4) { % Causes the clientbox to be shown at coordinate (#1,#2) and named #3
        \node[rectangle,draw=white,fill=white] at (#1,#2) (#3) {#4};
    }
}
\pgfoonew \myclient=new clientbox()
\begin{center}
  \begin{tikzpicture}[% List of styles applied to all, to override specify on a case-by-case
      every node/.style={
        align=center,      % use this so that the "\\" for line break works
        minimum size=2cm,  % creates space above and below text in rectangle
        minimum width=4cm
      },
      every edge/.style={draw,thick}
    ]
    \node[rectangle,ultra thick,draw=black,fill=blue,minimum width=8 cm](R2){\Comp};
    \node[rectangle,draw=white,fill=white](R5)[below= of R2]{timebase};
    \node[rectangle,draw=white,fill=white](placeholder)[above= of R2]{};
    \path[->]
    (R2)edge []  node [] {} (R5)
    (R5)edge []  node [] {} (R2)
    ;
    \gettikzxy{(placeholder)}{\rx}{\ry}
    \myclient.apply(\rx - 100,\ry,C1,\\ metadata);
    \path[<->]($(R2.north) + (-100 pt,0)$) edge [] node [] {} (C1);
    \myclient.apply(-\rx + 0,\ry,C1, \\ CPMaster control \\ plane interface);
    \path[<->]($(R2.north) + (0 pt,0)$) edge [] node [] {} (C1);
    \myclient.apply(-\rx + 100,\ry,C1, ``zynq\_ultra'' \\ SDP data plane \\ interface);
    \path[<->]($(R2.north) + (100 pt,0)$) edge [] node [] {} (C1);

  \end{tikzpicture}
\end{center}

\pagebreak

\tableofcontents
\listoffigures
\listoftables

\pagebreak

\section{Functionality}
  The \comp{} platform worker exposes the OpenCPI control plane, data plane, and
  timebase interface on the Xilinx Zynq UltraScale+ \soc{} \ZCUxxx{} Evaluation Kit
  \cite{\zcuxxx{}_website}. The control and data planes interface with the zeroth
  Zynq UltrsaScale+ High-performance AXI4 interface port (HP0). The worker uses
  the zeroth Zynq PS FCLK clock as the control plane, data plane, and timebase
  port clocks.

\section{Worker Implementation Details}
  The \comp{} platform worker instantiates version 3.2 of the Xilinx Zynq
  UltraScale+ Processing System LogiCORE IP core \cite{xilinx_pg201}.
  \begin{center}
  \framebox{
    \parbox{0.8\linewidth}{
      \centering
      \textcolor{red}{IMPORTANT:}
      This worker's references to AXI GP refer to the GP ports of the generated IP
      core. The UltraScale+ Device Technical Reference Manual (TRM) refers to
      the IP core's GP ports as High Performance (HP) ports. Note that the useGP1 property
      is disabled for this worker because software does not yet recognize this property change
      for the ZynqMP.
    }
  }
  \end{center}

\section{Source Dependencies}
  \begin{itemize}
    \item bsp\_\zcuxxx{}/hdl/platforms/\zcuxxx{}/\zcuxxx{}.vhd

    % zynq_ultra_ps_e
    \item bsp\_\zcuxxx{}/hdl/primitives/zynq\_ultra/vivado\_zynq\_ultra/zynq\_ultra\_ps\_e\_0.vhd
    \item bsp\_\zcuxxx{}/hdl/primitives/zynq\_ultra/vivado\_zynq\_ultra/zynq\_ultra\_ps\_e\_v3\_2\_1.v
    \item bsp\_\zcuxxx{}/hdl/primitives/zynq\_ultra/vivado\_zynq\_ultra/zynq\_ultra\_ps\_e\_pkg.vhd
    \item bsp\_\zcuxxx{}/hdl/primitives/zynq\_ultra/zynq\_ultra\_pkg.vhd
    \item bsp\_\zcuxxx{}/hdl/primitives/zynq\_ultra/zynq\_ultra\_ps\_e.vhd

    % bsv.bsv.SyncResetA
    \item opencpi/projects/core/hdl/primitives/bsv/bsv\_pkg.vhd
    \item opencpi/projects/core/hdl/primitives/bsv/imports/SyncResetA.v

    % m_axi_gp2hp, axi2cp, sdp2axi
    \item opencpi/projects/core/hdl/primitives/axi/axi2cp.vhd
    \item opencpi/projects/core/hdl/primitives/axi/axi\_pkg.vhd
    \item opencpi/projects/core/hdl/primitives/axi/m\_axi\_gp2hp.vhd
    \item opencpi/projects/core/hdl/primitives/sdp/sdp2axi\_rd.vhd
    \item opencpi/projects/core/hdl/primitives/sdp/sdp2axi\_wd.vhd
    \item opencpi/projects/core/hdl/primitives/sdp/sdp\_body.vhd
    \item opencpi/projects/core/hdl/primitives/sdp/sdp\_pkg.vhd
    \item opencpi/projects/core/hdl/primitives/sdp/sdp2axi.vhd
    \item opencpi/projects/core/hdl/primitives/sdp/sdp2axi\_addr36\_ent.vhd
    \item opencpi/projects/core/hdl/primitives/sdp/sdp\_axi\_addr36\_pkg.vhd
  \end{itemize}

\begin{landscape}
	\section{Worker Properties}
	\begin{scriptsize}
		\begin{tabular}{|p{3cm}|p{1.5cm}|c|c|c|p{1.5cm}|p{1cm}|p{6cm}|}
			\hline
			\rowcolor{blue}
			Name               & Type   & SequenceLength & ArrayDimensions & Accessibility      & Valid Range & Default & Usage                                                                         \\
			\hline
			\verb+platform+    & String & 31             & -               & Parameter & Standard & \zcuxxx{} & Name of this platform                                                     \\
			\hline
			\verb+sdp_width+   & UChar  & -              & -               & Parameter & Standard & 1 & Width of data plane in DWORDS                                             \\
			\hline
			\verb+UUID+        & ULong  & -              & 16              & Readable           & Standard    & -       & UUID of this platform                                                         \\
			\hline
			\verb+oldtime+     & ULongLong & -           & -               & Padding            & Standard    & -       & N/A                                                                           \\
			\hline
			\verb+romAddr+     & UShort & -              & -               & Writable           & Standard    & -       &                                                                               \\
			\hline
			\verb+romData+     & ULong  & -              & -               & Volatile           & Standard    & -       &                                                                               \\
			\hline
			\verb+nSwitches+   & ULong  & -              & -               & Readable           & Standard    & -       & Number of switches                                                            \\
			\hline
			\verb+nLEDs+       & ULong  & -              & -               & Readable           & Standard    & -       & Number of LEDs                                                                \\
			\hline
			\verb+memories_length+ & ULong & -           & -               & Readable           & Standard    & -       &                                                                               \\
			\hline
			\verb+memories+    & ULong  & -              & 4               & Readable           & Standard    & -       & The memory regions that may be used by \\
  	                     &        &                &                 &                    &             &         & various other elements, which          \\
  	                     &        &                &                 &                    &             &         & indicates aliasing etc.               \\
                         &        &                &                 &                    &             &         & The values describing each region are: \\
                         &        &                &                 &                    &             &         & Bit 31:28 - External bus/BAR connected \\
                         &        &                &                 &                    &             &         &             to this memory (0 is none) \\
                         &        &                &                 &                    &             &         & Bit 27:14 - Offset in bus/BAR of this  \\
                         &        &                &                 &                    &             &         &             memory (4KB units)         \\
                         &        &                &                 &                    &             &         & Bit  13:0 - Size of this memory (4KB units) \\
                         &        &                &                 &                    &             &         &             units) \\
			\hline
			\verb+dna+         & ULongLong & -           & -               & Readable           & Standard    & -       & DNA (unique chip serial number) of this platform \\
			\hline
			\verb+switches+    & ULong  & -              & -               & Volatile           & Standard    & -       & Current value of any switches in the platform                                 \\
			\hline
			\verb+led+        & ULong  & -              & -               & Writable, Readable & Standard    & -       & Setting of LEDs in the platform, with readback. A value of true illuminates the given LED. The indices and their corresponding LEDs are index 12: LED DS17, 11: DS18, 10: DS20, 9: DS19, 8: DS16, 7: unused, 6: DS22, 5: DS15, 4: DS13, 3: DS10, 2: DS9, 1: DS11, 0: unused. For example, writing a value of 0x1002 will illuminate only LEDs DS17 and DS11.\\
			\hline
			\verb+nSlots+      & ULong  & -              & -               & Parameter & Standard & 0 & Number of slots available for cards, which indicates the usable length of the slotCardIsPresent array property. \\
			\hline
			\verb+slotNames+   & String & 32             & -               & Parameter & Standard & ``'' & A string which is intended to include comma-separated names of the slots available for cards. The inter-comma position of each name corresponds to the same index of the slotCardIsPresent array property. \\
			\hline
			\verb+slotCardIsPresent+ & Bool & -          & 64              & Volatile           & Standard    & -       & An array of booleans, where each index contains an indication whether a card is physically present in the given index's slot. For a description of a given index's slot, see the corresponding comma-separated string contents in the slotName property. Note that only the first min(nSlots,64) of the 64 indices contain pertinent information. \\
			%\hline
			%\verb+useGP1+ & Bool & -          & -               & Parameter          & Standard    & False   & - \\
			\hline
			\verb+axi_error+ & Bool & -          & 4               & Volatile           & Standard    & -       & - \\
			\hline
			\verb+sdpDropCount+ & UChar & -          & -               & Volatile           & Standard    & -       & - \\
			\hline
			\verb+debug_state+ & ULongLong & -          & 4               & Volatile           & Standard    & -       & - \\
			\hline
			\verb+debug_state1+ & ULongLong & -          & 4               & Volatile           & Standard    & -       & - \\
			\hline
			\verb+debug_state2+ & ULongLong & -          & 4               & Volatile           & Standard    & -       & - \\
			\hline

		\end{tabular}
	\end{scriptsize}

	\section{Worker Ports}
	No ports are included in the component specification.

	\section{Worker Interfaces}
	\begin{scriptsize}
		\begin{tabular}{|M{2cm}|M{2cm}|M{1.5cm}|M{1.5cm}|M{14.5cm}|}
			\hline
			\rowcolor{blue}
			Type       & Name & Master & Count & Usage                  \\
			\hline
			metadata   & -    & true   & -     & Access to container metadata via the platform worker. All platform workers must provide this port. \\
			\hline
			timebase   & -    & true   & -     & Providing a timebase for the time service. All platform workers must provide this port. \\
			\hline
			cpmaster   & - & true   & -     & This platform worker provides a control plane. \\
			\hline
			sdp        & \verb+zynq_ultra+ & true   & 4     & - \\
			\hline
		\end{tabular}
	\end{scriptsize}

\end{landscape}
\pagebreak
	\section{Platform Devices}
	The following is a table which enumerates which device workers are allowed in platform configurations and in assembly containers. The parameter values specified restrict allowed implementations. Note that the worker signals listed are only those who are unconnected on the platform or whose platform signal name differ from the worker signal name. Note that device workers allowed by cards are not included in this list.\\
			\begin{tabular}{|M{3cm}|M{3.5cm}|M{3cm}|M{3cm}|M{3cm}|}
			\hline
			\rowcolor{blue}
			Name                       & Property Name    & Property Value              & Worker Signal & Platform Signal         \\
			\hline
			time\_server               & frequency        & 100*10\textsuperscript{6}   &               &                         \\
			\hline
		\end{tabular}

\section{Signals}
Note that this signal table does not include signals that may be provided by slots. \\
\begin{tabular}{|c|c|c|c|p{8cm}|}
	\hline
	\rowcolor{blue}
	Name           & Type   & Differential & Width & Description                                          \\
	\hline
	led            & Output & false        & 8    & -\\
	\hline
\end{tabular}
\section{Slots}
Note that slots exist on the \ZCUxxx{} board but that have not yet been interfaced with the platform worker.

\section{Platform Configurations}
	\begin{tabular}{|c|c|c|c|}
		\hline
		\rowcolor{blue}
		Name & Platform Configuration Workers & Card & Slot \\
		\hline
		\multirow{2}{*}{base} &\zcuxxx{} & - & - \\ &time\_server & - & - \\
		\hline
	\end{tabular}

\section{Control Timing and Signals}

\begin{landscape}
\section{Performance and Resource Utilization}
%\input{../../\ecomp/utilization.inc}
\end{landscape}

\section{Troubleshooting}
The UltraScale+ AXI HP registers \cite{ultrascaleplus_registers_website} can be inspected by running the following command on the \ZCUxxx{}.
\lstset{language=bash, backgroundcolor=\color{lightgray}, columns=flexible, breaklines=true, prebreak=\textbackslash, basicstyle=\ttfamily, showstringspaces=false,upquote=true, aboveskip=\baselineskip, belowskip=\baselineskip}
\begin{lstlisting}
ocpizynq axi_hp
\end{lstlisting}

\section{Test and Verification}
All of the application worker unit tests in the core and assets projects have been run succesfully on the \ZCUxxx{} platform. This effectively tests both the control and data planes in various scenarios.

\begin{thebibliography}{1}

  %\bibitem{github_opencpi_v1p4} Github - opencpi/opencpi at release\_1.4 \\
  %\url{https://github.com/opencpi/opencpi/tree/release_1.4}

  \bibitem{ultrascaleplus_registers_website} Zynq UltraScale+ MPSoC Register Reference \\
  \url{https://www.xilinx.com/html_docs/registers/ug1087/ug1087-zynq-ultrascale-registers.html}

  \bibitem{xilinx_ug1085} Zynq UltraScale+ Device Technical Reference Manual \\
  \url{https://www.xilinx.com/support/documentation/user_guides/ug1085-zynq-ultrascale-trm.pdf}

  \bibitem{xilinx_pg201} Zynq UltraScale+ MPSoC Processing System v3.2 Product Guide (PG201) \\
  \url{https://www.xilinx.com/support/documentation/ip_documentation/zynq_ultra_ps_e/v3_2/pg201-zynq-ultrascale-plus-processing-system.pdf}

  \bibitem{\zcuxxx{}_website} Zynq UltraScale+ \soc{} \ZCUxxx{} Evaluation Kit \\
  \url{\boarddoc}

\end{thebibliography}

\end{document}
