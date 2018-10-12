c$$$c     
c$$$c     ==================
c$$$      program z1a_driver
c$$$c     ==================
c$$$c     
c$$$c     Driver routine for the subroutine Z1ANIS for the computation
c$$$c     of magnetotelluric impedances on the surface of a 1-D layered
c$$$c     generally anisotropic medium
c$$$c     
c$$$c     Algorithm description:
c$$$c     ------------------------------------------------------------------
c$$$c     Pek, J. and Santos, F. A. M., 2002. Magnetotelluric impedances and
c$$$c     parametric sensitivities for 1-D generally anisotropic layered 
c$$$c     media, Computers & Geosciences, in print.
c$$$c     ------------------------------------------------------------------
c$$$c     
c$$$c     List of subroutines (4):
c$$$c     Z1ANIS, ROTZ, CPANIS, DPHASE
c$$$c     
c$$$c     Compiled with Compaq Visual Fortran Professional Edition 6.5.0
c$$$c     
c$$$      real*8 pi
c$$$      parameter(pi=3.14159265358979323846264338327950288d0)
c$$$      complex*16 ic
c$$$      parameter(ic=(0.d0,1.d0))
c$$$c     
c$$$c     > Maximum number of layers of the layered anisotropic model
c$$$c     
c$$$      parameter(nlmax=1001)
c$$$c     
c$$$      real*4 h(nlmax)
c$$$      real*4 rop(nlmax,3),ustr(nlmax),udip(nlmax),usla(nlmax)
c$$$      real*8 al(nlmax),at(nlmax),blt(nlmax),sg(nlmax,3,3)
c$$$      complex*16 z(2,2)
c$$$      real*8 omega,mu0,prev
c$$$      real*8 rapp(2,2),papp(2,2)
c$$$c     
c$$$c     > Open data file with model parameters and read the model data
c$$$c     
c$$$      open(1,file='an.dat')
c$$$c     
c$$$c     > NL .............. integer*4 number of layers including the basement
c$$$c     > H(NLMAX) ........ real*4 array with layer thickesses, in km. 
c$$$c     >                   Thickness of the basement, H(NL), may be arbitrary
c$$$c     > ROP(NLMAX,3) .... real*4 array of principal resistivities within the
c$$$c     >                   layers, 3 for each layer, in Ohm*m
c$$$c     > USTR(NLMAX) ..... real*4 array with anisotropy strikes of the layers,
c$$$c     >                   in degrees
c$$$c     > UDIP(NLMAX) ..... real*4 array with anisotropy dips of the layers,
c$$$c     >                   in degrees
c$$$c     > USLA(NLMAX) ..... real*4 array with anisotropy slants of the layers,
c$$$c     >                   in degrees
c$$$c     
c$$$      read(1,*)nl
c$$$      do layer=1,nl
c$$$         read(1,*)h(layer),(rop(layer,i),i=1,3),
c$$$     &        ustr(layer),udip(layer),usla(layer)
c$$$      enddo
c$$$      close(1)
c$$$c     
c$$$c     > Permeability of vacuum
c$$$c     
c$$$      mu0=4.d-7*pi
c$$$c     
c$$$c     > Open files for results
c$$$c     > AN.RES  contains model parameters and impedances on the surface 
c$$$c     >         of the anisotropic layered model
c$$$c     > ANR.RES contains a simple table with the apparent resistivities
c$$$c     >         and impedance phases for all periods involved
c$$$c     
c$$$      open(2,file='an.res')
c$$$      open(3,file='anr.dat')
c$$$c     
c$$$c     > Compute the equivalent parameters of an azimuthally anisotropic
c$$$c     > medium for all layers in the stack
c$$$c     > SG(NLMAX,3,3) ...... real*8 array with the components of the
c$$$c     >                      conductivity tensor, in S/m, for the layers
c$$$c     > AL(NLMAX) .......... real*8 array with the maximum horizontal
c$$$c     >                      conductivities, in S/m, for the layers
c$$$c     > AT(NLMAX) .......... real*8 array with the minimum horizontal
c$$$c     >                      conductivities, in S/m, for the layers
c$$$c     > BLT(NLMAX) ......... real*8 array with the effective horizontal
c$$$c     >                      anisotropy strikes, in radians, for the
c$$$c     >                      individual layers
c$$$c     
c$$$      call cpanis(rop,ustr,udip,usla,nl,sg,al,at,blt) 
c$$$c     
c$$$      write(2,'("=== Model parameters ====================")')
c$$$      write(2,*)
c$$$      do layer=1,nl
c$$$         write(2,'("+++> Layer = ",i5,", thickness in km = ",f12.4)')
c$$$     &        layer,h(layer)
c$$$         write(2,'("--- Conductivity tensor, in S/m ---------")')
c$$$         write(2,'("s_xx  s_xy  s_xz",2x,3f14.5)')(sg(layer,1,j),j=1,3)
c$$$         write(2,'("s_yx  s_yy  s_yz",2x,3f14.5)')(sg(layer,2,j),j=1,3)
c$$$         write(2,'("s_zx  s_zy  s_zz",2x,3f14.5)')(sg(layer,3,j),j=1,3)
c$$$         write(2,'("--- CONDMAX,CONDMIN,ASTRIKE for eq.mod. --")')
c$$$         write(2,'(5x,3f14.5)')al(layer),at(layer),
c$$$     &        180.d0*blt(layer)/pi
c$$$         write(2,*)
c$$$      end do
c$$$      write(2,'("=========================================")')
c$$$c     
c$$$c     > Fixed period range from 10**(-3) to 10**(+5) seconds, the period step
c$$$c     > is 0.2 in the logarithmic domain
c$$$c     
c$$$      do iper=-30,50,2          ! ciclo su periodo. 
c$$$c     
c$$$c     > Period of the field, in seconds
c$$$c     
c$$$         per=10.**(0.1*float(iper))
c$$$c     
c$$$c     > Compute MT impedances for the 1-D layered anisotropic model
c$$$c     
c$$$c     > Z(2,2) .............. complex*16 array with the elements of the 
c$$$c     >                       impedance tensor on the surface of the medium,
c$$$c     >                       in SI units (Ohm)
c$$$c     
c$$$         call z1anis(h,al,at,blt,nl,per,z)
c$$$c     
c$$$         write(2,*)
c$$$         write(2,'("=== Period and impedance tensor =========")')
c$$$         write(2,2001)
c$$$ 2001    format(8x,"PERIOD",4x,"Re Zxx",6x,"Im Zxx",6x,"Re Zxy",
c$$$     &   6x,"Im Zxy")
c$$$         write(2,2002)
c$$$ 2002    format(18x,"Re Zyx",6x,"Im Zyx",6x,"Re Zyy",6x,"Im Zyy")
c$$$c     
c$$$         write(2,'(f14.5,4e12.4)')per,z(1,1),z(1,2)
c$$$         write(2,'(14x,4e12.4)')z(2,1),z(2,2)
c$$$c     
c$$$c     > Compute apparent resistivities and impedance phases from the
c$$$c     > impedance tensor
c$$$c     
c$$$         omega=2.d0*pi/dble(per)
c$$$         prev=1.d0/(omega*mu0)
c$$$         do i=1,2
c$$$            do j=1,2
c$$$               rapp(i,j)=prev*cdabs(z(i,j))**2.d0
c$$$               papp(i,j)=180.d0*dphase(z(i,j))/pi
c$$$            enddo
c$$$         enddo
c$$$c     
c$$$c     
c$$$         write(2,'("--- Period, resistivities and phases ----")')
c$$$         write(2,2003)
c$$$ 2003    format(8x,"PERIOD",4x,"RHOAxx",6x,"RHOAxy",6x,"RHOAyx",6x,
c$$$     &   "RHOAyy")
c$$$         write(2,2004)
c$$$ 2004    format(18x,"PHIAxx",6x,"PHIAxy",6x,"PHIAyx",6x,"PHIAyy")
c$$$         write(2,'(f14.5,4(1pe12.4))')per,rapp(1,1),rapp(1,2),
c$$$     &        rapp(2,1),rapp(2,2)
c$$$         write(2,'(14x,4f12.2)')papp(1,1),papp(1,2),
c$$$     &        papp(2,1),papp(2,2)
c$$$         write(3,'(f14.5,4(1pe12.4,2x,0pf12.2))')per,
c$$$     &        rapp(1,1),papp(1,1),
c$$$     &        rapp(1,2),papp(1,2),
c$$$     &        rapp(2,1),papp(2,1),
c$$$     &        rapp(2,2),papp(2,2)
c$$$      enddo
c$$$c     
c$$$      close(2)
c$$$      close(3)
c$$$c     
c$$$      stop
c$$$      end
c$$$c     
c$$$c
c$$$c===> SUBROUTINE Z1ANIS
c     =======================================
      subroutine z1anis(h,al,at,blt,nl,per,z)
c     =======================================
c     Stable impedance propagation procedure for 1-D layered
c     media with generally anisotropic layers
c
c     Input:
c     ------
c     H(NLMAX).........real*4 array of layer thicknesses in km. 
c                      Any value may be input as a thickness of                    
c                      the homogeneous basement
c     AL(NLMAX)........real*8 array of maximum horizontal con-
c                      ductivities of the layers in S/m
c     AT(NLMAX)........real*8 array of minimum horizontal con-
c                      ductivities of the layers in S/m
c     BLT(NLMAX).......real*8 array of equivalent horizontal
c                      anisotropy strikes of the layers in
c                      radians
c     NL...............integer*4 number of layers in the model
c                      including the basement, NL<=NLMAX
c     PER..............real*4 period of the elmg field in s
c
c     Output:
c     -------
c     Z(2,2)...........complex*16 array with the elements of the
c                      impedance tensor on the surface in SI units
c                      (Ohm). The arrangement is as follows
c                         | Z_xx  Z_xy | = | Z(1,1)  Z(1,2) |
c                         | Z_yx  Z_yy | = | Z(2,1)  Z(2,2) |
c
      real*8 pi
      parameter(pi=3.14159265358979323846264338327950288d0)
      complex*16 ic
      parameter(ic=(0.d0,1.d0))
c
      parameter(nlmax=1001)
c
      real*8 h(nlmax)
      real*8 al(nlmax),at(nlmax),blt(nlmax)
      real*8 per
      complex*16 z(2,2)
c
      complex*16 x,dfp,dfm
      complex*16 iom,k0,k1,k2
      complex*16 zrot(2,2),zbot(2,2),dtzbot,zdenom
      complex*16 dz1,dz2,ag1,ag2
      real*8 omega,mu0
      real*8 a1,a2,bs,hd,bsref,a1is,a2is
c
      dfp(x)=1.d0+cdexp(-2.d0*x)
      dfm(x)=1.d0-cdexp(-2.d0*x)
c
c      write(112,*) blt
c      
      omega=2.d0*pi/dble(per)
      mu0=4.d-7*pi
      iom=-ic*omega*mu0
      k0=(1.d0-ic)*2.d-3*pi/dsqrt(10.d0*dble(per))
c
c> Compute the impedance on the top of the homogeneous
c> basement in the direction of its strike
c

      layer=nl
      a1=al(layer)
      a2=at(layer)
      bs=blt(layer)
      
c
      k1=k0*dsqrt(a1)
      k2=k0*dsqrt(a2)
      c2bs=dcos(2.d0*bs)
      s2bs=dsin(2.d0*bs)
      a1is=1.d0/dsqrt(a1)
      a2is=1.d0/dsqrt(a2)
c
      zrot(1,1)=0.d0
      zrot(1,2)=k0*a1is
      zrot(2,1)=-k0*a2is
      zrot(2,2)=0.d0
c
c> If no more layers are present in the model, rotate the
c> impedance into the original coordinate system and return
c
      if(nl.eq.1)then
        call rotz(zrot,-bs,z)
        return
      endif
c
c> Set the reference direction to the anisotropy strike of
c> the current layer
c
      bsref=bs
c
c> Process the rest of the layers above the basement
c
      nl1=nl-1
      do layer=nl1,1,-1
        hd=1.d+3*dble(h(layer))
        a1=al(layer)
        a2=at(layer)
        bs=blt(layer)

c
c> If the strike direction differs from that of the previous
c> layer, rotate the impedance into the coordinate system of
c> the current anisotropy strike
c
        dtzbot=zrot(1,1)*zrot(2,2)-zrot(1,2)*zrot(2,1)
        if(bs.ne.bsref.and.a1.ne.a2)then
          call rotz(zrot,bs-bsref,zbot)
        else
          zbot(1,1)=zrot(1,1)
          zbot(1,2)=zrot(1,2)
          zbot(2,1)=zrot(2,1)
          zbot(2,2)=zrot(2,2)
          bs=bsref
        endif
c
        k1=k0*dsqrt(a1)
        k2=k0*dsqrt(a2)
        a1is=1.d0/dsqrt(a1)
        a2is=1.d0/dsqrt(a2)
        dz1=k0*a1is
        dz2=k0*a2is
        ag1=k1*hd
        ag2=k2*hd
c
c> Propagate the impedance tensor from the bottom to the top
c> of the current layer
c
        zdenom=dtzbot*dfm(ag1)*dfm(ag2)/(dz1*dz2)+
     &         zbot(1,2)*dfm(ag1)*dfp(ag2)/dz1-
     &         zbot(2,1)*dfp(ag1)*dfm(ag2)/dz2+
     &         dfp(ag1)*dfp(ag2)
        zrot(1,1)=4.d0*zbot(1,1)*cdexp(-ag1-ag2)/zdenom
        zrot(1,2)=(zbot(1,2)*dfp(ag1)*dfp(ag2)-
     &             zbot(2,1)*dfm(ag1)*dfm(ag2)*dz1/dz2+
     &             dtzbot*dfp(ag1)*dfm(ag2)/dz2+
     &             dfm(ag1)*dfp(ag2)*dz1)/zdenom
        zrot(2,1)=(zbot(2,1)*dfp(ag1)*dfp(ag2)-
     &             zbot(1,2)*dfm(ag1)*dfm(ag2)*dz2/dz1-
     &             dtzbot*dfm(ag1)*dfp(ag2)/dz1-
     &             dfp(ag1)*dfm(ag2)*dz2)/zdenom
        zrot(2,2)=4.d0*zbot(2,2)*cdexp(-ag1-ag2)/zdenom
c
c> Set the reference direction to the anisotropy strike of
c> the current layer and go on to the next layer
c
        bsref=bs
c
      enddo
c
c> On the surface, rotate the impedance into the original
c> coordinate system and return
c
      if(bsref.ne.0.d0)then
        call rotz(zrot,-bsref,z)
      else
        z(1,1)=zrot(1,1)
        z(1,2)=zrot(1,2)
        z(2,1)=zrot(2,1)
        z(2,2)=zrot(2,2)
      endif
c
      return
c
      end
c===> END SUBROUTINE Z1ANIZ
c
c
c===> SUBROUTINE ROTZ
c     =============================
      subroutine rotz(za,betrad,zb)
c     =============================
c     Rotates the impedance ZA by BETRAD (in radians) to obtain ZB
c
      real*8 betrad
      complex*16 za(2,2),zb(2,2)
c
      real*8 co2,si2
      complex*16 sum1,sum2,dif1,dif2
c
      co2=dcos(2.d0*betrad)
      si2=dsin(2.d0*betrad)
c
      sum1=za(1,1)+za(2,2)
      sum2=za(1,2)+za(2,1)
      dif1=za(1,1)-za(2,2)
      dif2=za(1,2)-za(2,1)
c
      zb(1,1)=0.5d0*(sum1+dif1*co2+sum2*si2)
      zb(1,2)=0.5d0*(dif2+sum2*co2-dif1*si2)
      zb(2,1)=0.5d0*(-dif2+sum2*co2-dif1*si2)
      zb(2,2)=0.5d0*(sum1-dif1*co2-sum2*si2)
c
      return
      end
c===> END SUBROUTINE ROTZ
c
c
c===> SUBROUTINE CPANIS
c     =====================================================
      subroutine cpanis(rop,ustr,udip,usla,nl,sg,al,at,blt)
c     =====================================================
c     Computes effective azimuthal anisotropy parameters in 
c     anisotropic layers from their principal resistivities
c     and elementary anisotropic directions
c
c     Input:
c     ------
c     ROP(NLMAX,3).....real*4 array of principal resistivities
c                      of the anisotropic layers in Ohm*m
c     USTR(NLMAX)......real*4 array with the anisotropy strike
c                      (first Euler's rotation) of the layers 
c                      in degrees
c     UDIP(NLMAX)......real*4 array with the anisotropy dip
c                      (second Euler's rotation) of the layers 
c                      in degrees
c     USLA(NLMAX)......real*4 array with the anisotropy slant
c                      (third Euler's rotation) of the layers 
c                      in degrees
c     NL...............integer*4 number of layers in the model
c                      including the basement, NL<=NLMAX
c
c     Output:
c     -------
c     SG(NLMAX,3,3)....real*8 array with conductivity tensor
c                      elements of the individual layers of the
c                      anisotropic model in S/m. The tensor is
c                      always symmetric and positive definite
c     AL(NLMAX)........real*8 array with the maximum effective
c                      horizontal conductivities of the layers 
c                      in S/m
c     AT(NLMAX)........real*8 array with the minimum effective
c                      horizontal conductivities of the layers 
c                      in S/m
c     BLT(NLMAX).......real*8 array with the effective horizontal
c                      anisotropy strike (direction of the maximum
c                      conductivity) of the layers in RADIANS
c
      real*8 pi
      parameter(pi=3.14159265358979323846264338327950288d0)
c
      parameter(nlmax=1001)
c
      real*4 rop(nlmax,3),ustr(nlmax),udip(nlmax),usla(nlmax)
      real*8 sgp(nlmax,3),sg(nlmax,3,3)
      real*8 al(nlmax),at(nlmax),blt(nlmax)
c
      real*8 rstr,rdip,rsla,sps,cps,sth,cth,sfi,cfi
      real*8 pom1,pom2,pom3,c2ps,s2ps,c2th,s2th,csps,csth
      real*8 axx,axy,ayx,ayy,da12
c
      do layer=1,nl
c
        do j=1,3
          sgp(layer,j)=1.d0/dble(rop(layer,j))
        enddo
c
        rstr=pi*dble(ustr(layer))/180.d0
        rdip=pi*dble(udip(layer))/180.d0
        rsla=pi*dble(usla(layer))/180.d0
        sps=dsin(rstr)
        cps=dcos(rstr)
        sth=dsin(rdip)
        cth=dcos(rdip)
        sfi=dsin(rsla)
        cfi=dcos(rsla)
        pom1=sgp(layer,1)*cfi*cfi+sgp(layer,2)*sfi*sfi
        pom2=sgp(layer,1)*sfi*sfi+sgp(layer,2)*cfi*cfi
        pom3=(sgp(layer,1)-sgp(layer,2))*sfi*cfi
        c2ps=cps*cps
        s2ps=sps*sps
        c2th=cth*cth
        s2th=sth*sth
        csps=cps*sps
        csth=cth*sth
c
c> Conductivity tensor
c
        sg(layer,1,1)=pom1*c2ps+pom2*s2ps*c2th-2.*pom3*cth*csps+
     &                sgp(layer,3)*s2th*s2ps
        sg(layer,1,2)=pom1*csps-pom2*c2th*csps+pom3*cth*(c2ps-s2ps)-
     &                sgp(layer,3)*s2th*csps
        sg(layer,1,3)=-pom2*csth*sps+pom3*sth*cps+sgp(layer,3)*csth*sps
        sg(layer,2,1)=sg(layer,1,2)
        sg(layer,2,2)=pom1*s2ps+pom2*c2ps*c2th+2.*pom3*cth*csps+
     &                sgp(layer,3)*s2th*c2ps
        sg(layer,2,3)=pom2*csth*cps+pom3*sth*sps-sgp(layer,3)*csth*cps
        sg(layer,3,1)=sg(layer,1,3)
        sg(layer,3,2)=sg(layer,2,3)
        sg(layer,3,3)=pom2*s2th+sgp(layer,3)*c2th
c
c> Effective horizontal 2*2 conductivity tensor
c
        axx=sg(layer,1,1)-sg(layer,1,3)*sg(layer,3,1)/sg(layer,3,3)
        axy=sg(layer,1,2)-sg(layer,1,3)*sg(layer,3,2)/sg(layer,3,3)
        ayx=sg(layer,2,1)-sg(layer,3,1)*sg(layer,2,3)/sg(layer,3,3)
        ayy=sg(layer,2,2)-sg(layer,2,3)*sg(layer,3,2)/sg(layer,3,3)
c
c> Principal conductivities and anisotropy strike of the effective
c> horizontal conductivity tensor
c
        da12=dsqrt((axx-ayy)*(axx-ayy)+4.d0*axy*ayx)
        al(layer)=0.5d0*(axx+ayy+da12)
        at(layer)=0.5d0*(axx+ayy-da12)
c
c> Intrinsic function TINY(real_argument) (Microsoft/Compaq Fortran)
c> gives the smallest number in the model representing the same type 
c> and kind parameters as the argument. Alternatives are IMSL functions
c> AMACH(1) or DMACH(1) that give the smallest normalized positive 
c> number in the computer's single-precision or double-precision
c> arithmetic, respectively, or adequate functions for machine constants
c> determination on other systems
c
        if(da12.ge.tiny(da12))then
          blt(layer)=(axx-ayy)/da12
          blt(layer)=0.5d0*dacos(blt(layer))
        else
          blt(layer)=0.d0
        endif
        if(axy.lt.0.d0)blt(layer)=-blt(layer)
c
      enddo
c
      return
      end
c===> END SUBROUTINE CPANIS
c
c
c===> REAL*8 FUNCTION DPHASE
c     ===========================
      real*8 function dphase(z16)
c     ===========================
c     Computes real*8 phase of a complex*16 value Z16
c     
      real*8 pi
      parameter(pi=3.14159265358979323846264338327950288d0)
c     
      complex*16 z16
      real*8 pom
c     
      if(dabs(dreal(z16)).ge.tiny(pom))then
         pom=datan(dimag(z16)/dreal(z16))
         if(dreal(z16).lt.0.d0)then
            if(dimag(z16).ge.0.d0)then
               dphase=pom+pi
            else
               dphase=pom-pi
            endif
         else
            dphase=pom
         endif
      else
         if(dimag(z16).lt.tiny(pom))then
            dphase=0.d0
         else
            if(dimag(z16).gt.0.d0)then
               dphase=5.d-1*pi
            else
               dphase=-5.d-1*pi
            endif
         endif
      endif
c     
c      write(*,*) 'dphase', dphase
      return
      end
c===  > END REAL*8 FUNCTION DPHASE
c
c
