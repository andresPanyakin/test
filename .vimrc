"----------------------------------------------------STANDART-----------------------------------------------
" This line should not be removed as it ensures that various options are
" properly set to work with the Vim-related packages available in Debian.
runtime! debian.vim

" Uncomment the following to have Vim jump to the last position when
" reopening a file
if has("autocmd")
  au BufReadPost * if line("'\"") > 1 && line("'\"") <= line("$") | exe "normal! g'\"" | endif
endif

" Uncomment the following to have Vim load indentation rules and plugins
" according to the detected filetype.
if has("autocmd")
  filetype plugin indent on
endif

" Source a global configuration file if available
if filereadable("/etc/vim/vimrc.local")
  source /etc/vim/vimrc.local
endif

"Распознавание типов файлов и типо-специфичные плагины.
filetype on
filetype plugin on

colorscheme wombat256mod

"-------------------------------------------COMMON----------------------------------------------------------------------
set nocompatible                    "Отключаем совместимость со старым VI
set shortmess+=I                    "Отключаем детей Уганды
set showcmd                         "Show (partial) command in status line.
set showmatch                       "Show matching brackets.
set ignorecase                      "Do case insensitive matching
set smartcase                       "Do smart case matching
set incsearch                       "Incremental search
set autowrite                       "Automatically save before commands like :next and :make
set hidden                          "Hide buffers when they are abandoned
set mouse=v                         "Enable mouse usage (all modes)
set mousehide                       "Прятать мышку во время ввода текста
set termencoding=utf-8              "Кодировка терминала
set encoding=utf-8                  "Кодировки файлов по умолчанию
set fileencodings=utf8,cp1251       "Возможные кодировки файлов, если файл не в unicode кодировке
set number                          "Показывать номера строк
set numberwidth=4                   "Число цифр, выделенных для номеров строк
set hlsearch                        "Подсветка поиска
set wrap                            "Динамический перенос длинных строк
set linebreak                       "Переносить целые слова
set nobackup                        "Отключаем создание back-up
set noswapfile                      "Отключить создание swap files
set expandtab                       "Преобразование таба в пробелы
set softtabstop=4                   "Делаем в табе 4 пробела
set shiftwidth=4                    "Автоматический отступ при переходе на новую строку
set tabstop=4                       "Говорим, сколько пробелов должно быть в табе
set foldenable                      "Включить фолдинг
set foldmethod=indent               "Определять блоки по блоку
set foldcolumn=1                    "Колоночка, чтобы показывать плюсики для скрытия блоков кода
set updatetime=0                    "Время обновления окна 0 мс
set foldlevel=99                    "Определяем уровень вложенности
set showtabline=2                   "Показывать табы
set autoindent                      "Включить автоотступы
set t_Co=256                        "Нужен для работы всех цветовых схем
set ruler                           "Все время показывать положение курсора в правом нижнем углу
set smartindent                     "Включить умные отступы
set scrolloff=3                     "Чтобы не нужно было передвигать курсор к краю экрана, чтобы опуститься
set wildmenu                        "Показывать доступные варианты над командной строкой
set secure                          "Запрещает писать в .vimrc и .exerc во время редактирования
set modelines=0                     "Из соображений безопасности
set undofile                        "создает файл с отмененными изменениями
set ttyfast
set smarttab
set langmap=Ж:,йq,чx,гu,шi

"Не показвать данные расширения в wildmenu
set wildignore=*.swp,*.o,*.d,*.pyc,*.*~

"Для плагина Pathogen
call pathogen#runtime_append_all_bundles()
call pathogen#helptags()

"---------------------------------------SYNTAX HIGHLIGHTING------------------------------------------------------------
"Включить подсветку синтаксиса
syntax on
syntax enable
"--------------------------------------AUTOCOMPLETE--------------------------------------------------------------------
set ofu=syntaxcomplete#Complete     "Автодополнение для Omni completion

"Auto complete по табу
"function InsertTabWrapper()
"    let col = col('.') - 1
"    if !col || getline('.')[col - 1] !~ '\k'
"        return "\<tab>"
"    else
"        return  "\<c-p>"
"    endif
"endfunction

"imap <tab> <c-r>=InsertTabWrapper()<cr>

"Откуда будем завершать:
set complete=""
set complete+=.                     "Из текущего буфера
set complete+=k                     "Из словаря
set complete+=b                     "Из других открытых буферов
set complete+=t                     "Из тегов

let g:snippetsEmu_key= "<c-j>"      "Автодополнение по Ctrl+J для Snippets Emu

"-----------------------------------------------MAPS--------------------------------------------------------
map <C-n> <C-PageDown>                  "Переход по вкладкам по Ctrl+n
map s :w<CR>                            "Сохранение по s
map q :q<CR>                            "Выход по q
nnoremap / /\v
vnoremap / /\v
nnoremap <leader><space> :noh<cr>
nnoremap <tab> %
vnoremap <tab> %

"Отключаем работу F1
inoremap <F1> <ESC>
vnoremap <F1> <ESC>
nnoremap <F1> <ESC>

"Удаляем все лишние пробелы в конце
nnoremap <leader>w :%s/\s\+$//<cr>:let @/=''<CR> 

"Теперь не надо нажимать Shift, чтобы ввести команду
nnoremap ; :

"Автоматически открываем .vimrc чтобы запилить туда что-нибудь новое
nnoremap <leader>ev <C-w><C-v><C-l>:e $MYVIMRC<cr>

"Теперь для смены режимов используется Ctrl-C
inoremap <C-c> <ESC>

nnoremap <F7> :NERDTree<cr>


"Работа со сплитам
"
"Мапим сплит и сразу переходим в новое окно
nnoremap <leader>w <C-w>v<C-w>l

"Мапим переходы по окнам
nnoremap <C-h> <C-w>h
nnoremap <C-j> <C-w>j 
nnoremap <C-k> <C-w>k
nnoremap <C-l> <C-w>l

let python_higlight_all=1

"---------------------------------------------CSCOPE && CTAGS-------------------------------------------------------------
if has("cscope")
if filereadable("cscope.out")
cs add cscope.out
elseif $CSCOPE_DB !=""
    cs add $CSCOPE_DB
endif
endif

cs add /home/andres/projects/andress-toros_2/cscope.out /home/andres/projects/andress-toros_2/
cs add /home/andres/Debug/linux-3.0.12/cscope.out /home/andres/Debug/
cs add /home/andres/projects/glibc/cscope.out /home/andres/projects/glibc

set tags+=/home/andres/projects/andress-toros_2/tags
set tags+=/home/andres/projects/glibc/tags
set tags+=/home/andres/Debug/linux-3.0.12/tags

