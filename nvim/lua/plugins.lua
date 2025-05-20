vim.call('plug#begin', '~/.config/nvim/plug')
local Plug = vim.fn['plug#']

Plug 'http://github.com/tpope/vim-surround'
Plug 'https://github.com/preservim/nerdtree' 
Plug 'nvim-treesitter/nvim-treesitter'
Plug 'nvim-lua/plenary.nvim'
Plug 'nvim-telescope/telescope.nvim'
Plug 'chentoast/marks.nvim'

Plug 'mfussenegger/nvim-dap'
Plug 'nvim-neotest/nvim-nio'
Plug 'rcarriga/nvim-dap-ui'
Plug 'mfussenegger/nvim-dap-python'

-- Plug 'https://github.com/tpope/vim-commentary'
-- Plug 'https://github.com/neoclide/coc.nvim'
Plug 'https://github.com/vim-airline/vim-airline'
Plug 'vim-airline/vim-airline-themes'
-- Plug 'https://github.com/tc50cal/vim-terminal'
-- Plug 'tpope/vim-dispatch'
Plug 'https://github.com/vim-scripts/errormarker.vim'
Plug ('catppuccin/nvim', { as = 'catppuccin' })

Plug 'Vigemus/iron.nvim'
-- -- Plug 'dense-analysis/ale'

Plug 'MeanderingProgrammer/render-markdown.nvim'

Plug 'robitx/gp.nvim'
vim.call('plug#end')
