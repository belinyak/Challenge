(setq buildPath "c:/Users/Belinyak/Documents/GitHub/Challenge/Misc/build.bat" )
(setq runPath "c:/Users/Belinyak/Documents/GitHub/Challenge/Misc/run.bat" )
(setq todoPath "c:/Users/Belinyak/Documents/GitHub/Challenge/Misc/todo.bat" )
(setq navPath "c:/Program Files (x86)/GNU Emacs/nav/" )

(setq undo-limit 20000000)
(setq undo-strong-limit 40000000)

;Turn off 
(setq blink-matching-paren nil)

;Smooth scroll
(setq scroll-step 3)

;Turn off the toolbar
(tool-bar-mode 0)
(show-paren-mode 0)
(menu-bar-mode -1)

;enable to delete selection
(delete-selection-mode 1)

;auto bracket complete
(electric-pair-mode 1)
(setq electric-pair-open-newline-between-pairs t)

;Startup windowing
(setq next-line-add-newlines nil)
(setq-default truncate-lines t)
(setq truncate-partial-width-windows nil)
(split-window-horizontally)

;ScrollBar
(scroll-bar-mode -1)

;unset middle mouse button
(global-unset-key [mouse-2])

;HighLight Current Line
(global-hl-line-mode 1)
(set-face-background 'hl-line "midnight blue")

; Handle super-tabbify (TAB completes, shift-TAB actually tabs)
(setq dabbrev-case-replace t)
(setq dabbrev-case-fold-search t)
(setq dabbrev-upcase-means-case-search t)

; Abbrevation expansion (autocomplete)
 (abbrev-mode 1)


(define-abbrev-table 'c++-mode-abbrev-table '(
("todo" ["//TODO(mate): " 0 () nil] expand-abbrev-hook 0)
("note" ["//NOTE(mate): " 0 () nil] expand-abbrev-hook 0)
("guard" ["#ifndef \n#define \n #endif \n " 20 () nil] expand-abbrev-hook 0)
 ))
    
;------------------------------------------------------------------------------------------------
;CM color theme
;(add-to-list 'default-frame-alist '(font . "Liberation Mono-9"))
(set-face-attribute 'font-lock-builtin-face nil :foreground "#DAB98F")
(set-face-attribute 'font-lock-comment-face nil :foreground "gray50")
(set-face-attribute 'font-lock-constant-face nil :foreground "olive drab")
(set-face-attribute 'font-lock-doc-face nil :foreground "gray50")
(set-face-attribute 'font-lock-function-name-face nil :foreground "burlywood3")
(set-face-attribute 'font-lock-keyword-face nil :foreground "DarkGoldenrod3")
(set-face-attribute 'font-lock-string-face nil :foreground "olive drab")
(set-face-attribute 'font-lock-type-face nil :foreground "burlywood3")
(set-face-attribute 'font-lock-variable-name-face nil :foreground "burlywood3")
(set-foreground-color "burlywood3")
(set-background-color "#161616")
(set-cursor-color "#40FF40")

(load-library "view")
(require 'cc-mode)
(require 'ido)
(require 'compile)
(ido-mode t)

(setq c-default-style "linux"
         c-basic-offset 4)
;(setq c-basic-offset 4)

;------------------------------------------------------------------------------------------------
; C++ indentation style
(defconst casey-big-fun-c-style
  '(;(c-electric-pound-behavior   . nil)
    (c-tab-always-indent         . t)
    (c-comment-only-line-offset  . 0)
    (c-hanging-braces-alist      . ((class-open)
                                    (class-close)
                                    (defun-open)
                                    (defun-close)
                                    (inline-open)
                                    (inline-close)
                                    (brace-list-open)
                                    (brace-list-close)
                                    (brace-list-intro)
                                    (brace-list-entry)
                                    (block-open)
                                    (block-close)
                                    (substatement-open)
                                    (statement-case-open)
                                    (class-open)))
    (c-hanging-colons-alist      . ((inher-intro)
                                    (case-label)
                                    (label)
                                    (access-label)
                                    (access-key)
                                    (member-init-intro)))
    (c-cleanup-list              . (scope-operator
                                    list-close-comma
                                    defun-close-semi))
    (c-offsets-alist             . ((arglist-close         .  c-lineup-arglist)
                                    (label                 . -4)
                                    (access-label          . -4)
                                    (substatement-open     .  0)
                                    (statement-case-intro  .  4)
                                    (statement-block-intro .  c-lineup-for)
                                    (case-label            .  4)
                                    (block-open            .  0)
                                    (inline-open           .  0)
                                    (topmost-intro-cont    .  0)
                                    (knr-argdecl-intro     . -4)
                                    (brace-list-open       .  0)
                                    (brace-list-intro      .  4)))
    (c-echo-syntactic-information-p . t))
    "Casey's Big Fun C++ Style")

; CC++ mode handling
(defun casey-big-fun-c-hook ()

; Set my style for the current buffer
(c-add-style "BigFun" casey-big-fun-c-style t)
 
; 4-space tabs
(setq tab-width 4
indent-tabs-mode nil)

; Additional style stuff
(c-set-offset 'member-init-intro '++))

; Bright-red TODOs
 (setq fixme-modes '(c++-mode c-mode emacs-lisp-mode))
 (make-face 'font-lock-fixme-face)
 (make-face 'font-lock-note-face)
 (mapc (lambda (mode)
	 (font-lock-add-keywords
	  mode
	  '(("\\<\\(TODO\\)" 1 'font-lock-fixme-face t)
            ("\\<\\(NOTE\\)" 1 'font-lock-note-face t))))
	fixme-modes)
 (modify-face 'font-lock-fixme-face "Red" nil nil t nil t nil nil)
 (modify-face 'font-lock-note-face "Dark Green" nil nil t nil t nil nil)

; Accepted file extensions and their appropriate modes
(setq auto-mode-alist
      (append
       '(("\\.cpp$"    . c++-mode)
         ("\\.hin$"    . c++-mode)
         ("\\.cin$"    . c++-mode)
         ("\\.inl$"    . c++-mode)
         ("\\.rdc$"    . c++-mode)
         ("\\.h$"    . c++-mode)
         ("\\.c$"   . c++-mode)
         ("\\.cc$"   . c++-mode)
         ("\\.c8$"   . c++-mode)
         ("\\.txt$" . indented-text-mode)
         ("\\.emacs$" . emacs-lisp-mode)
         ("\\.gen$" . gen-mode)
         ("\\.ms$" . fundamental-mode)
         ("\\.m$" . objc-mode)
         ("\\.mm$" . objc-mode)
         ) auto-mode-alist))


;------------------------------------------------------------------------------------------------
;Shortcuts

(put 'kill-ring-save 'interactive-form
     '(interactive
       (if (use-region-p)
           (list (region-beginning) (region-end))
         (list (line-beginning-position) (line-beginning-position 2)))))
    (put 'kill-region 'interactive-form      
     '(interactive
       (if (use-region-p)
           (list (region-beginning) (region-end))
        (list (line-beginning-position) (line-beginning-position 2)))))

(global-set-key (kbd "\C-v") 'yank) ; paste
(define-key c++-mode-map "\C-v" 'yank)
(global-set-key (kbd "\C-x") 'kill-region) ; paste
(define-key c++-mode-map "\C-x" 'kill-region)
(global-set-key (kbd "\C-c") 'kill-ring-save) ; paste
(define-key c++-mode-map "\C-c" 'kill-ring-save)


;cut/copy/paste
;cut/copy/paste

;open file
(global-set-key (kbd "C-o") 'find-file )
(global-set-key (kbd "C-S-o") 'find-file-other-window )


;save file
(global-set-key (kbd "C-s") 'save-buffer )

;(global-set-key (kbd "C-S-o") 'open-buffer)

;undo
(global-set-key (kbd "C-z") 'undo )

;select current word
(global-set-key (kbd "C-w") 'mark-word )

;change tab/open in other tab/create tab
(global-set-key (kbd "<f1>") 'other-window)
;search
(global-set-key (kbd "C-f") 'isearch-forward )
(define-key isearch-mode-map "\C-f" 'isearch-repeat-forward)
;search and replace
(global-set-key (kbd "C-h") 'replace-string )

;unset

(global-set-key (kbd "M-<left>") 'previous-buffer)  ; Alt+↑
(global-set-key (kbd "M-<right>") 'next-buffer)  ; Alt+↑

;; move line up
(defun move-line-up ()
  (interactive)
  (transpose-lines 1)
  (previous-line 2))

;; move line down
(defun move-line-down ()
  (interactive)
  (next-line 1)
  (transpose-lines 1)
  (previous-line 1))

(global-set-key (kbd "M-<up>") 'move-line-up)  ; Alt+↑
(global-set-key (kbd "M-<down>") 'move-line-down)  ; Alt+↑
;------------------------------------------------------------------------------------------------

(global-set-key (kbd "C-i") 'indent-region )

(define-key c++-mode-map "\C-m" 'newline-and-indent)
(setq c-hanging-semi&comma-criteria '((lambda () 'stop)))

(setq compilation-directory-locked nil)
  (setq casey-makescript "build.bat")

;(define-key global-map "C-e" 'first-error)
(global-set-key (kbd "C-S-e") 'previous-error)
(global-set-key (kbd "C-e") 'next-error)

(global-set-key (kbd "C-a") 'mark-whole-buffer)

;(global-set-key [tab]'dabbrev-expand)
 (define-key c++-mode-map "\t" 'dabbrev-expand)
 (define-key c++-mode-map [C-tab] 'indent-for-tab-command)
;(global-set-key [C-tab] 'indent-for-tab-command)

;------------------------------------------------------------------------------------------------
; Compilation
(setq compilation-context-lines 0)
(setq compilation-error-regexp-alist
    (cons '("^\\([0-9]+>\\)?\\(\\(?:[a-zA-Z]:\\)?[^:(\t\n]+\\)(\\([0-9]+\\)) : \\(?:fatal error\\|warnin\\(g\\)\\) C[0-9]+:" 2 3 nil (4))
     compilation-error-regexp-alist))

(defun build ()
  "Make the curren build."
  (interactive)
 (compile buildPath))

(defun run()
  "run the exe."
  (interactive)
 (compile runPath))

(defun todo()
  "run todo.bat"
  (interactive)
 (compile todoPath))

;; by Nikolaj Schumacher, 2008-10-20. Released under GPL.
(defun semnav-up (arg)
  (interactive "p")
  (when (nth 3 (syntax-ppss))
    (if (> arg 0)
        (progn
          (skip-syntax-forward "^\"")
          (goto-char (1+ (point)))
          (decf arg))
      (skip-syntax-backward "^\"")
      (goto-char (1- (point)))
      (incf arg)))
  (up-list arg))

;; by Nikolaj Schumacher, 2008-10-20. Released under GPL.
(defun extend-selection (arg &optional incremental)
  "Select the current word.
Subsequent calls expands the selection to larger semantic unit."
  (interactive (list (prefix-numeric-value current-prefix-arg)
                     (or (and transient-mark-mode mark-active)
                         (eq last-command this-command))))
  (if incremental
      (progn
        (semnav-up (- arg))
        (forward-sexp)
        (mark-sexp -1))
    (if (> arg 1)
        (extend-selection (1- arg) t)
      (if (looking-at "\\=\\(\\s_\\|\\sw\\)*\\_>")
          (goto-char (match-end 0))
        (unless (memq (char-before) '(?\) ?\"))
          (forward-sexp)))
      (mark-sexp -1))))

(global-set-key (kbd "C-w") 'extend-selection)

(global-set-key (kbd "C-b") 'build )
(define-key global-map [f5] 'run )
(define-key global-map [f6] 'todo )
(global-set-key (kbd "C-q") 'c-fill-paragraph)

(defun smart-open-line-above ()
  "Insert an empty line above the current line.
Position the cursor at it's beginning, according to the current mode."
  (interactive)
  (move-beginning-of-line nil)
  (newline-and-indent)
  (forward-line -1)
  (indent-according-to-mode))

(global-set-key [(control return)] 'smart-open-line-above)
(global-set-key [C-delete] 'kill-whole-line)



;------------------------------------------------------------------------------------------------

;fullscreen
(defun maximize-frame ()
  "Maximize frame"
  (interactive)
  (w32-send-sys-command 61488))
 
 (global-set-key [(f4)] 'maximize-frame)

(defun post-load-stuff ()
  (maximize-frame)
)
(add-hook 'window-setup-hook 'post-load-stuff t)

(add-to-list 'load-path navPath)
 (require 'nav)
 (nav-disable-overeager-window-splitting)
(global-set-key (kbd "C-t")  'nav-toggle)
;------------------------------------------------------------------------------------------------

; SUMMARY

;abbrevs

; todo "//TODO(mate): " 
; note "//NOTE(mate): " 
; guard "#ifndef \n#define \n #endif \n "


; C-c         copy
; C-x         cut 
; C-v         paste
; C-o         open file 
; C-S-o       open file other window 
; C-s         save file

; C-z         undo 

; C-f         search 
; C-f         next occurence
; C-h         search and replace 

; Alt-left    previous-buffer 
; Alt-right   next-buffer

; C-ret       open line above line
; C-del       delete line

; Alt-up      move line up
; Alt-down    move line down

; C-e         next error
; C-S-e       previous error

; C-a         select all
; C-w         select word 

; C-i         indent region 
; C-q         format comment
; C-tab       indent

; tab         dabbrev expand

; C-b         build 
; F5          run 
; F6          todo 

; F1          change window
; C-t         open explorer view
