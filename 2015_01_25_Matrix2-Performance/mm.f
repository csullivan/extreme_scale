      program main
      implicit none
      integer matSize, maxTest
      parameter (matSize=1100)
      parameter (maxTest=10)
      double precision mysecond
      external mysecond
      double precision matA(matSize,matSize), matB(matSize,matSize),       &
     &                 matC(matSize,matSize), sum
      integer i, j, k, tests
      double precision tStart, tEnd, tLoop, t, rate
!
!     Initialize the matrices
!     Note that this is *not* in the best order with respect to cache;
!     this will be discussed later in the course.
      do i=1,matSize
         do j=1,matSize
            matA(i,j) = 1.0 + i
            matB(i,j) = 1.0 + j
            matC(i,j) = 0.0
         enddo
      enddo
!
      tLoop = 1.0e10
      do tests=1,maxTest
         tStart = mysecond()
         do i=1,matSize
            do j=1,matSize
               sum = 0.0
               do k=1,matSize
                  sum = sum + matA(i,k)*matB(k,j)
               enddo
               matC(i,j) = sum
            enddo
         enddo
         tEnd = mysecond()
         call dummy(matA, matB, matC)
         t = tEnd - tStart
! Save minimum of measured times
         if (t .lt. tLoop) tLoop = t
         if (matC(1,1) .lt. 0.0) then
            print *, 'Failed matC sign test'
         endif
      enddo
!
! Note that explicit formats are used to limit the number of
! significant digits printed (at most this many digits are significant)
      write(*,'(" Matrix size = ",i6)') matSize
      write(*,'(" Time        = ",1pe10.2," secs")') tLoop
      rate = (2.0 * matSize) * matSize * (matSize / tLoop)
      write(*,'(" Rate        = ",1pe10.2," MFLOP/s")') rate*1.0e-6

      end
