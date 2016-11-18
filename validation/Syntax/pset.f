C     Bug: too many arguments in the call to RUN (at the end)
C     Modification: a dummy RUN procedures with a wrong number of
C     arguments was added

C
C  *********************************************************************
C  *   SUBROUTINE TO SET THE ARRAY POINTERS FOR VECTORIZING THE CODE.  *
C  *********************************************************************
C
      SUBROUTINE PSET(NX,NY,NZ,NT,NTIME,NWINDX,NWINDY,NSINKS,NFILT,
     *XSTART,YSTART,ZSTART,TSTART,DELTAX,DELTAY,DELTAZ,DELTAT,PHI,DL,
     *DX,DY,DZ,WORK,IB,IK,ITY,NCOUNT,NPRINT,NGRAPH,NPSTEP,NGSTEP)
      DIMENSION  WORK(*)
      CHARACTER DUMMY
      COMMON/LAKE/SX,SIGX,SY,SIGY,ZNOT,SFX,SFY,FLX,FLY,BASE,TSL,H0,ZW,ZL
      COMMON/SOURCE/INIT(2,2),NSOUR(2),IX(2,2),JY(2,2),KZ(2,2),
     * IVAL(2,2),NSX(2,2),NSY(2,2),NSZ(2,2),ISR(2,2)
      COMMON/LEVEL/KK1,KK2,KK3,KK4,IYHOM,IGEO,IUGX,IVGY,LT0,LT1,ICPU
      COMMON/STRCH/ALP,BET,DH,ZH,UG,VG,T1,T2,DT,TOL,ALPHA,HAMP,BUMP
      COMMON/CPU/CINIT,CINHC,CINVC,CINHT,CINVT,CINPI,CINHU,CINVU,
     *CINHV,CINVV,CINHW,CINVW,CINPR,CINBL,CINFL,CINMN,TM1,TM18,TM19
C
C **   SEPARATE DIMENSIONALITY OF PROGRAM
C
      L3=NX*NY*NZ
      L2=NX*NY
      L1=NZ
C
C ===== ALLOCATION OF GLOBAL MEMORY FOR PARAMETERS IN VECTOR FORM  =====
C
C **   MESO-CONCENTRATION OF ONE POLLUTANT C(X,Y,Z,T)                 **
      LC=1
      LAST=L3
C **   PREVIOUS STEPS OF C(X,Y,Z,T-1) FOR THE TIME SCHEME             **
      LCSTEP=LAST+1
      LAST=LAST+L3
C **   MESO-PERTURBATION POTENTIAL TEMPERATURE POTT(X,Y,Z,T)          **
      LPOT=LAST+1
      LAST=LAST+L3
C **   PREVIOUS STEPS OF POTT(X,Y,Z,T-1) FOR THE TIME SCHEME          **
      LTSTEP=LAST+1
      LAST=LAST+L3
C **   MESO-PERTURBATION U - WIND COMPONENT UX(X,Y,Z,T)               **
      LUX=LAST+1
      LAST=LAST+L3
C **   PREVIOUS STEPS OF UX(X,Y,Z,T-1) FOR THE TIME SCHEME            **
      LUSTEP=LAST+1
      LAST=LAST+L3
C **   MESO-PERTURBATION V - WIND COMPONENT VY(X,Y,Z,T)               **
      LVY=LAST+1
      LAST=LAST+L3
C **   PREVIOUS STEPS OF VY(X,Y,Z,T-1) FOR THE TIME SCHEME            **
      LVSTEP=LAST+1
      LAST=LAST+L3
C **   MESO-PERTURBATION W - WIND COMPONENT WZ(X,Y,Z,T)               **
      LWZ=LAST+1
      LAST=LAST+L3
C **   MESO-PERTURBATION PRESSURE PI PRESS(X,Y,Z,T)                   **
      LPI=LAST+1
      LAST=LAST+L3
C **   PREVIOUS STEP OF PRESSURE PI PRESS(X,Y,Z,T)                    **
      LPSTEP=LAST+1
      LAST=LAST+L3
C **   SOURCES OR SINKS FOR THE POLLUTANTS  C,  Q(X,Y,Z)              **
      LQ=LAST+1
      LAST=LAST+L3
C **   DIFFUSSIVITY COEFFICIENT FOR MOMENTUM DKZ(X,Y,Z)=DKZM(X,Y,Z)   **
      LDKZM=LAST+1
      LAST=LAST+L3
C **   DIFFUSSIVITY COEFFICIENT FOR HEAT DKZ(X,Y,Z)=DKZH(X,Y,Z)       **
      LDKZH=LAST+1
      LAST=LAST+L3
C **   TERRAIN ELEVATION IN METERS ELEV(X,Y)                          **
      LELEV=LAST+1
      LAST=LAST+L2
C **   TERRAIN X-GRADIENT IN METERS ELEVX(X,Y)                        **
      LELEVX=LAST+1
      LAST=LAST+L2
C **   TERRAIN Y-GRADIENT IN METERS ELEVY(X,Y)                        **
      LELEVY=LAST+1
      LAST=LAST+L2
C **   ROUGHNESS LENGTH OF TERRAIN IN METERS Z0(X,Y)                  **
      LZ0=LAST+1
      LAST=LAST+L2
C **   MIXING HEIGHT OR BOUNDARY LAYER HEIGHT HMIX(X,Y)               **
      LHMIX=LAST+1
      LAST=LAST+L2
C **   MIXING HEIGHT AT THE PREVIOUS TIME STEP STEPH(X,Y)             **
      LSTEPH=LAST+1
      LAST=LAST+L2
C **   MEAN TEMPERATURE IN THE SURFACE LAYER TAVR(X,Y)                **
      LTAVR=LAST+1
      LAST=LAST+L2
C **   MONIN-OBUKHOV LENGTH OBUK(X,Y)                                 **
      LOBUK=LAST+1
      LAST=LAST+L2
C **   FRICTION VELOCITY USTAR USTR(X,Y)                              **
      LUSTR=LAST+1
      LAST=LAST+L2
C **   TURBULENT  TEMPERATURE THETASTAR TSTR(X,Y)                     **
      LTSTR=LAST+1
      LAST=LAST+L2
C **   DRY DEPOSITION VELOCITY VDEP(X,Y)                              **
      LVDEP=LAST+1
      LAST=LAST+L2
C **   SURFACE DEPOSITION OF  POLLUTANTS  DEP(X,Y)                    **
      LDEP=LAST+1
      LAST=LAST+L2
C **   VERTICAL HEIGHT Z  ZET(Z)                                      **
      LZET=LAST+1
      LAST=LAST+L1
C **   UNEQUAL POINT STRECHED PARAMETER  DH/DZ = HVAR(Z)              **
      LHVAR=LAST+1
      LAST=LAST+L1
C **   MEAN OR SYNOPTIC U-WIND COMPONENT  UM(Z)                       **
      LUM=LAST+1
      LAST=LAST+L1
C **   MEAN OR SYNOPTIC V-WIND COMPONENT  VM(Z)                       **
      LVM=LAST+1
      LAST=LAST+L1
C **   GEOSTROPHIC U-WIND COMPONENT  UG(Z)                            **
      LUG=LAST+1
      LAST=LAST+L1
C **   GEOSTROPHIC V-WIND COMPONENT  VG(Z)                            **
      LVG=LAST+1
      LAST=LAST+L1
C **   MEAN OR SYNOPTIC POTENTIAL TEMPERATURE TM(Z)                   **
      LTM=LAST+1
      LAST=LAST+L1
C **   MEAN OR SYNOPTIC EDDY DIFFUSSIVITY DKM(Z)                      **
      LKM=LAST+1
      LAST=LAST+L1
C
C  =====       ALLOCATION OF AUXILIARY WORK SPACE     ==================
C
C **   DERIVATIVES WITH RESPECT TO X  DCDX(X,Y,Z)                     **
      LDCDX=LAST+1
      LAST=LAST+L3
C **   DERIVATIVES WITH RESPECT TO Y  DCDY(X,Y,Z)                     **
      LDCDY=LAST+1
      LAST=LAST+L3
C **   HELP VECTOR FOR PADE SCHEME -CENTER ELEMENTS-                  **
      LAN=LAST+1
      LAST=LAST+L1
C **   HELP VECTOR FOR PADE SCHEME -LEFT   ELEMENTS-                  **
      LBN=LAST+1
      LAST=LAST+L1
C **   HELP VECTOR FOR PADE SCHEME -RIGHT  ELEMENTS-                  **
      LCN=LAST+1
      LAST=LAST+L1
C **   UTILITY VECTOR FOR NUMERICAL WORK                              **
      LHELP=LAST+1
      LAST=LAST+MAX(NX,NY,NZ)
C **   ANOTHER UTILITY VECTOR FOR DIRTY WORK                          **
      LHELPA=LAST+1
      LAST=LAST+MAX(NX,NY,NZ)
C **    WORK VECTOR FOR THE X-FFT                                     **
      LSAVEX=LAST+1
      LAST=LAST+2*NX+15
C **    WORK VECTOR FOR THE Y-FFT                                     **
      LSAVEY=LAST+1
      LAST=LAST+2*NY+15
C **    X-WAVENUMBERS  FOR FIRST DERIVATIVES                          **
      LFX=LAST+1
      LAST=LAST+NX*0.5
C **    X- WEIGHTS FOR HEAT AND POLLUTANTS X,Y SPECTRAL DIFFUSION     **
      LFXC=LAST+1
      LAST=LAST+NX
C **    X - WEIGHTS FOR MOMENTUM HORIZONTAL SPECTRAL DIFFUSION        **
      LFXX=LAST+1
      LAST=LAST+NX*0.5
C **    Y-WAVENUMBERS FOR FIRST DERIVATIVES                           **
      LFY=LAST+1
      LAST=LAST+NY*0.5
C **    Y- WEIGHTS FOR HEAT AND POLLUTANTS X,Y SPECTRAL DIFFUSION     **
      LFYC=LAST+1
      LAST=LAST+NY
C **    Y - WEIGHTS FOR MOMENTUM HORIZONTAL SPECTRAL DIFFUSION        **
      LFYY=LAST+1
      LAST=LAST+NY*0.5
C **    X - FILTER FOR DERIVATIVE  DIFFUSION                          **
      LFILX=LAST+1
      LAST=LAST+NX
C **    Y - FILTER FOR DERIVATIVE  DIFFUSION                          **
      LFILY=LAST+1
      LAST=LAST+NY
C **    Z - FILTER FOR THE SPONGE LAYER IN Z                          **
      LFILZ=LAST+1
      LAST=LAST+NZ
C
C     MAKE A LAST CHECK
C
      WRITE(6,'(A,I8,A)') ' WORK ARRAY HAS ',LAST,
     1' ELEMENTS.  '
      IF(NWINDX.EQ.1) PAUSE
C
C
C   ====================================================================
C   *   THIS SUBROUTINE RUN DOES ALL CALCULATIONS  AND ALLOCATES       *
C   *   GLOBAL TO STATIC MEMORY FOR VECTOR OPERATIONS                  *
C   ====================================================================
C
C
      CALL RUN(NX,NY,NZ,NT,NTIME,NWINDX,NWINDY,NSINKS,NFILT,XSTART,
     * YSTART,ZSTART,TSTART,DELTAX,DELTAY,DELTAZ,DELTAT,PHI,DL,
     * DX,DY,DZ,IB,IK,ITY,NCOUNT,NPRINT,NGRAPH,NPSTEP,NGSTEP,LAST,
     * WORK(LC),WORK(LCSTEP),WORK(LPOT),WORK(LTSTEP),WORK(LUX),
     * WORK(LUSTEP),WORK(LVY),WORK(LVSTEP),WORK(LWZ),WORK(LPI),
     * WORK(LPSTEP),WORK(LQ),WORK(LDKZM),WORK(LDKZH),WORK(LELEV),
     * WORK(LELEVX),WORK(LELEVY),WORK(LZ0),WORK(LHMIX),WORK(LSTEPH),
     * WORK(LTAVR),WORK(LOBUK),WORK(LUSTR),WORK(LTSTR),WORK(LVDEP),
     * WORK(LDEP),WORK(LZET),WORK(LHVAR),WORK(LUM),WORK(LVM),WORK(LUG),
     * WORK(LVG),WORK(LTM),WORK(LKM),WORK(LDCDX),WORK(LDCDY),WORK(LAN),
     * WORK(LBN),WORK(LCN),WORK(LHELP),WORK(LHELPA),WORK(LSAVEX),
     * WORK(LSAVEY),WORK(LFX),WORK(LFXC),WORK(LFXX), WORK(LFY),
     * WORK(LFYC),WORK(LFYY), WORK(LFILX),WORK(LFILY),WORK(LFILZ))
C
      RETURN
      END
      SUBROUTINE RUN
     * (NX,NY,NZ,NT,NTIME,NWINDX,NWINDY,NSINKS,NFILT,XSTART,
     * YSTART,ZSTART,TSTART,DELTAX,DELTAY,DELTAZ,DELTAT,PHI,DL,
     * DX,DY,DZ,IB,IK,ITY,NCOUNT,NPRINT,NGRAPH,NPSTEP,NGSTEP,LAST)
      CONTINUE
      END
