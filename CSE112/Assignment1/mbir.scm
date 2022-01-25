#! /afs/cats.ucsc.edu/courses/cse112-wm/usr/racket/bin/mzscheme -qr
;; Edwin Wang and Brian Zhao (ekwang and bwzhao respectively)
;; $Id: mbir.scm,v 1.2 2020-09-06 20:23:54-07 - - $
;;
;; NAME
;;    mbir.scm filename.mbir
;;
;; SYNOPSIS
;;    mbir.scm - mini basic interper
;;
;; DESCRIPTION
;;    The file mentioned in argv[1] is read and assumed to be an mbir
;;    program, which is the executed.  Currently it is only printed.
;;

(define *DEBUG* #f)
(define *STDIN* (current-input-port))
(define *STDOUT* (current-output-port))
(define *STDERR* (current-error-port))
(define *ARG-LIST* (vector->list (current-command-line-arguments)))

(define *stmt-table*     (make-hash))
(define *function-table* (make-hash))
(define *var-table*      (make-hash))
(define *array-table*    (make-hash))
(define *label-table*    (make-hash))

;; HELPER FUNCTION(S)

;; Check for labels
(define (check-labels program)
  (let* ([line (cdar program)]
    [nextline (cdr program)])
    ;; If line is not empty
    (if (pair? line)
        ;; If line does not start with a pair then car line is our label
        (if (pair? (car line))
             (void)
             (hash-set! *label-table* (car line) program))
        (void))
    (if (null? nextline) (void) (check-labels nextline)))
    )

;; END OF HELPER FUNCTION(S)

;; Filling hashtable var-table
(for-each (lambda (var) (hash-set! *var-table* (car var) (cadr var)))
 `(
  (e    ,(exp 1.0))
  (eof  ,0)
  (nan  ,(/ 0.0 0.0))
  (pi   ,(acos -1.0))
  ))

;; Filling hashtable function-table
(for-each (lambda (var)
  (hash-set! *function-table* (car var) (cadr var)))
`(
  (+    ,+)
  (-    ,-)
  (*    ,*)
  (/    ,(lambda (x y) (/ (+ x 0.0) (+ y 0.0))))
  (^    ,expt)
  (log  ,(lambda (x) (/ (log (+ x 0.0)) (log 10.0))))
  (sqrt ,sqrt)
  (atan ,atan)
  (exp  ,exp)
  (<=   ,<=)
  (>=   ,>=)
  (!=   ,=) ;; Handled at the higher level
  (=    ,=)
  (<    ,<)
  (>    ,>)
  (sin  ,sin)
  (cos  ,cos)
  (tan  ,tan)
  (acos ,acos)
  (asin ,asin)
  (abs  ,abs)
  (ceil ,ceiling)
  (floor,floor)
  (round,round)
  ))

(define *RUN-FILE*
  (let-values
    (((dirpath basepath root?)
      (split-path (find-system-path 'run-file))))
    (path->string basepath))
  )

(define (die list)
  (for-each (lambda (item) (fprintf *STDERR* "~s " item)) list)
  (fprintf *STDERR* "~n")
  (when (not *DEBUG*) (exit 1)))

(define (dump . args)
  (when *DEBUG*
    (printf "DEBUG:")
    (for-each (lambda (arg) (printf " ~s" arg)) args)
    (printf "~n")))

(define (usage-exit)
  (die `("Usage: " ,*RUN-FILE* " [-d] filename"))
  )

(define (line-number line)
  (car line))

(define (line-label line)
  (let ((tail (cdr line)))
   (and (not (null? tail))
    (symbol? (car tail))
    (car tail))))

(define (line-stmt line)
  (let ((tail (cdr line)))
   (cond ((null? tail) #f)
     ((pair? (car tail)) (car tail))
     ((null? (cdr tail)) #f)
     (else (cadr tail)))))

;; Called if a method is not implemented yet
(define (not-implemented function args . nl)
  (printf "(NOT-IMPLEMENTED: ~s ~s)" function args)
  (when (not (null? nl)) (printf "~n")))

;; Fully implemented eval-expr expr
(define (eval-expr expr)
  (cond
    ((number? expr) expr)
    ((memory? expr) (memory expr))
    (#t
      (let ((op (hash-ref *function-table* (car expr)))) 
        (apply op (map eval-expr (cdr expr)))))))

;; Helper functions for memory stuff
(define (memory expr)
  (cond
    ((arrayref? expr) (arrayref expr))
    ((variable? expr) (variable expr))))

(define (memory-set! mem val)
  (cond
    ((arrayref? mem) (arrayref-set! mem val))
    ((variable? mem) (variable-set! mem val))))

(define (memory? expr)
  (or
    (arrayref? expr)
    (variable? expr)))

(define (arrayref expr)
  (let ((name (cadr expr))
        (index (round (eval-expr (caddr expr)))))
    (if (hash-has-key? *array-table* name)
      (let ((vect (hash-ref *array-table* name)))
        (if ( <= index (vector-length vect))
          (vector-ref vect (inexact->exact index))
          (die `(Out of bounds error for ,name))))
        (die `(Vector ,name does not exist)))))

(define (arrayref-set! mem val)
  (let ((name (cadr mem))
        (index (eval-expr (caddr mem))))
    (if (hash-has-key? *array-table* (cadr mem))
      (vector-set!
        (hash-ref *array-table* name)
        (inexact->exact index)
        val)
      (die `(Vector ,name does not exist)))))
 
(define (arrayref? var)
  (and (pair? var)
       (equal? (car var) 'asub)
       (equal? (length var) 3)))

(define (variable expr)
  (if (hash-has-key? *var-table* expr)
    (hash-ref *var-table* expr)
    0.0))

(define (variable-set! mem val)
  (hash-set! *var-table* mem val))

(define (variable? expr)
  (symbol? expr))

;; Untested method interp-dim args continuation
(define (interp-dim args continuation)
  (hash-set! *array-table* (cadar args)
    (make-vector 
        (exact-round (eval-expr (caddar args))) 0.0))
  (interp-program continuation))

;; Fully implemeneted interp-let args continuation
(define (interp-let args continuation)
  (memory-set! (car args) (eval-expr (cadr args)))
  (interp-program continuation))

;; Fully implemented interp-goto args continuation
(define (interp-goto args continuation)
  (if (null? (hash-ref *label-table* (car args)))
    (interp-program continuation)
    (interp-program (hash-ref *label-table* (car args)))))

;; Fully implemented interp-if args continuation
(define (interp-if args continuation)
  ;; This accessor to grab the operation is correct
  (let ((op (caar args)))
    (if (eq? op '!=)
        (if (not (eval-expr (car args)))
            (interp-program (hash-ref *label-table* (cadr args)))
            (interp-program continuation))
        (if (eval-expr (car args))
            (interp-program (hash-ref *label-table* (cadr args)))
            (interp-program continuation)))))

;; interp-print args continuation completed in starter code
(define (interp-print args continuation)
  (define (print item)
    (if (string? item)
      (printf "~a" item)
      (printf " ~a" (eval-expr item))))
  (for-each print args)
    (printf "~n");
    (interp-program continuation))

;; Implemented interp-input args continuation for single input
(define (interp-input args continuation)
  (let ((input (read))) 
    (if (eof-object? input)
      (memory-set! 'eof 1.0)
      (memory-set! (car args) input)))
  (if (null? (cdr args))
    (interp-program continuation)
    (interp-input (cdr args) continuation)))

;; Populated stmt-table in starter code
(for-each (lambda (fn) (hash-set! *stmt-table* (car fn) (cadr fn)))
 `(
  (dim   ,interp-dim)
  (let   ,interp-let)
  (goto  ,interp-goto)
  (if    ,interp-if)
  (print ,interp-print)
  (input ,interp-input)
  ))

;; Main loop in starter code, when another line, continue interpreting
(define (interp-program program)
  (when (not (null? program))
    (let ((line (line-stmt (car program)))
      (continuation (cdr program)))
    (if line
     (let ((func (hash-ref *stmt-table* (car line) #f)))
      (func (cdr line) continuation))
     (interp-program continuation)))))

;; Reading input file in starter code
(define (readlist filename)
  (let ((inputfile (open-input-file filename)))
   (if (not (input-port? inputfile))
     (die `(,*RUN-FILE* ": " ,filename ": open failed"))
     (let ((program (read inputfile)))
      (close-input-port inputfile)
      program))))

;; If error in main loop, dump in starter code
(define (dump-program filename program)
  (define (dump-line line)
    (dump (line-number line) (line-label line) (line-stmt line)))
  (dump *RUN-FILE* *DEBUG* filename)
  (dump program)
  (for-each (lambda (line) (dump-line line)) program))

;; Argument handling in starter code
(define (main arglist)
  (cond ((null? arglist)
    (usage-exit))
  ((string=? (car arglist) "-d")
    (set! *DEBUG* #t)
    (printf "~a: ~s~n" *RUN-FILE* *ARG-LIST*)
    (main (cdr arglist)))
  ((not (null? (cdr  arglist)))
    (usage-exit))
  (else (let* ((mbprogfile (car arglist))
   (program (readlist mbprogfile)))
  (check-labels program)
                ;; Calling main loop interp-program program
                (begin (when *DEBUG* (dump-program mbprogfile program))
                 (interp-program program))))))

;; Passing arguments into main method in starter code
(main *ARG-LIST*)

