vim.g.mapleader = ' '
vim.g.maplocalleader = ","
vim.g.home = vim.fn.expand("~")

vim.cmd 'syntax on'
vim.cmd 'filetype plugin indent on'
vim.opt.autoindent = true
vim.opt.completeopt = 'menu,menuone,noinsert'
-- vim.opt.clipboard:append {'unnamed', 'ussamedplus' }

-- Copy to clipboard
vim.keymap.set({'n','v','x'}, '<leader>y', '"+y', { noremap = true})
vim.keymap.set({'n','v','x'}, '<leader>Y', '"+yg_', { noremap = true})
vim.keymap.set({'n','v','x'}, '<leader>d', '"+d', { noremap = true})
vim.keymap.set({'n','v','x'}, '<leader>D', '"+dg_', { noremap = true})
vim.keymap.set({'n','v','x'}, '<leader>p', '"+p', { noremap = true})
vim.keymap.set({'n','v','x'}, '<leader>P', '"+P', { noremap = true})

vim.opt.number = true
vim.opt.relativenumber = true
vim.opt.tabstop = 2 vim.opt.shiftwidth = 2
vim.opt.smarttab = true
vim.opt.softtabstop = 2
vim.opt.expandtab = true 
vim.opt.mouse = 'a'

vim.opt.splitbelow = true
vim.opt.splitright = true
vim.opt.title = true
vim.opt.ignorecase = true
vim.opt.wrap = false
vim.opt.so = 5 -- scroll-off

vim.cmd 'colorscheme catppuccin-mocha'
vim.cmd [[
  hi Normal guibg=NONE ctermbg=NONE
  hi NormalNC guibg=NONE ctermbg=NONE
  hi EndOfBuffer guibg=NONE ctermbg=NONE
  hi SignColumn guibg=NONE ctermbg=NONE
]]

vim.g.airline_extensions = {}
vim.g.airline_theme = "catppuccin" -- "transparent"
vim.g.airline_section_b = "" -- branch info
vim.g.airline_section_c = "" -- filename
vim.g.airline_section_x = "" --- vim filetype
vim.g.airline_section_y = "" -- encoding
vim.g.airline_section_error = "" 
vim.g.airline_section_warning = ""
vim.g.airline_section_z = "%l:%c"
 -- Ctrl-a to select all
vim.cmd 'map <C-a> <Esc>ggVG<CR>'


require'nvim-treesitter.configs'.setup {
  ensure_installed = { "cpp", "python", "javascript", "lua", "vim", "vimdoc", "markdown"},
  highlight = {
    enable = true, -- Enable highlighting
    additional_vim_regex_highlighting = true, -- Set to true if you need compatibility with old Vim regex highlights
  },
}

local builtin = require('telescope.builtin')
vim.keymap.set('n', '<leader>ff', builtin.find_files, { desc = 'Telescope find files' })
vim.keymap.set('n', '<leader>fg', builtin.live_grep, { desc = 'Telescope live grep' })
vim.keymap.set('n', '<leader>fb', builtin.buffers, { desc = 'Telescope buffers' })
vim.keymap.set('n', '<leader>fh', builtin.help_tags, { desc = 'Telescope help tags' })
local actions = require("telescope.actions")
require('telescope').setup{
  defaults = {
    mappings = {
      i = {
        ["<C-c>"] = actions.close,
      },
      n = {
        ["<C-c>"] = actions.close,
        ["s"] = actions.select_vertical,  -- Open in vertical split (NERDTree style)
        ["t"] = actions.select_tab,       -- Open in new tab = actions.close
      }
    }
  }
}

require'marks'.setup {
  default_mappings = false,
  cyclic = true,
  force_write_shada = false,
  refresh_interval = 250,
  sign_priority = { lower=10, upper=15, builtin=8, bookmark=20 }
}

require('render-markdown').setup({
  latex = {
    -- Turn on / off latex rendering.
    enabled = true,
    -- Additional modes to render latex.
    render_modes = false,
    -- Executable used to convert latex formula to rendered unicode.
    converter = vim.g.home .. '/repos/scripts/venv3.12/bin/latex2text',
    -- Highlight for latex blocks.
    highlight = 'RenderMarkdownMath',
    -- Determines where latex formula is rendered relative to block.
    -- | above | above latex block |
    -- | below | below latex block |
    position = 'above',
    -- Number of empty lines above latex blocks.
    top_pad = 0,
    -- Number of empty lines below latex blocks.
    bottom_pad = 0,
  }
})
