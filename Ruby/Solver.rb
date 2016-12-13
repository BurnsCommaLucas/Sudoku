#!/usr/bin/env ruby

require "enumerator"

#helper method for creating lists of units
def cross(a, b)
  return a.map{|i| b.map{|j| "#{i}#{j}" }}.flatten
end

#creates lists of columns, rows, units, etc.
$digits   = ["1", "2", "3", "4", "5", "6", "7", "8", "9"]
$rows     = ["A", "B", "C", "D", "E", "F", "G", "H", "I"]
$cols     = $digits
$squares  = cross($rows, $cols)

colsList = $cols.map{|c| cross($rows, [c])}

rowsList = $rows.map{|r| cross([r], $cols)}

rs     = [["A", "B", "C"], ["D", "E", "F"], ["G", "H", "I"]]
cs   = [[1, 2, 3], [4, 5, 6], [7, 8, 9]]

squaresList = []
#squaresList = rs.map{|r| cs.map{|c| cross(r, c)}}
$rows.each_slice(3) do |rs|
  $cols.each_slice(3) do |cs|
    squaresList << cross(rs, cs)
  end
end

$unitList = colsList + rowsList + squaresList

$units = Hash.new()
$squares.each{|s| $units[s] = $unitList.select{|u| u.include?(s)}}

$peers = Hash.new()
$squares.each{|s| $peers[s] = $units[s].flatten.uniq.select{|s2| s2 != s}}

def all(seq)
  for e in seq do return false if not e end
  return true
end

def some(seq)
  for e in seq do return e if e end
  return false
end


# Parse a grid

# Done, untested
def parse_grid(grid)
  # Convert grid to a dict of possible values, {square: digits}, or
  # return False if a contradiction is detected.
  ## To start, every square can be any digit; then assign values from the grid.
  values = {}
  $squares.map{|s| values[s] = deep_copy($digits)}
  grid_values(grid).each{|s, d| return false if $digits.include?(d.to_i) and not assign(values, s, d)}
  return values
end

# Done, untested
def grid_values(grid)
  # Convert grid into a dict of {square: char} with '0' or '.' for empties.
  chars = grid.split(//).select{|c| c if "1234567890.".include?(c)}
  return false if chars.size != 81
  return Hash[$squares.zip(chars)]
end

#Constraint Propagation

def assign(values, s, d)
  # Eliminate all the other values (except d) from values[s] and propagate.
  # Return values, except return False if a contradiction is detected.
  other_values = values[s].select{|d2| d2 != d}
  return values if all(other_values.map{|d2| eliminate(values, s, d2)})
  return false
end


def eliminate (values, s, d)
  # Eliminate d from values[s]; propagate when values or places <= 2.
  # Return values, except return False if a contradiction is detected.
  return values if not values[s].include?(d)
  values[s].delete(d)
  return false if values[s].size == 0
  return false if values[s].size == 1 and not all($peers[s].map{|s2| eliminate(values, s2, values[s][0])})
  for u in $units[s]
    dplaces = u.select{|s| values[s].include?(d)}
    return false if dplaces.size == 0
    return false if dplaces.size == 1 and not assign(values, dplaces[0], d)
  end
  return values
end

# Display in puzzle form
def display(values)
  width = 1+($squares.map{|s| values[s].size}).max
  line = "+".join(["-"*width*3]*3)
  for r in $rows
    for c in $cols
      val_string = values["#{r}#{c}"].join
      print val_string + (" " *(width -val_string.size))
      print "|" if c ==3 or c ==6
    end

    puts ""
    puts line if r == "C" or r =="F"
  end
end


# #Search
#
def solve(grid)
  return search(parse_grid(grid))
end


def search(values)
  return false if values == false
  return values if all($squares.map{|s| (values[s].size == 1)})
  unsolved = ($squares.select{|s| values[s].size > 1})
  s = unsolved.sort_by{|s| values[s].size}.first
  return some(values[s].map{|d| search(assign(deep_copy(values), s, d))})

end
#
#
# # Utilities
#
#
# def from_file(filename, sep='\n')
#
# end


def shuffled(seq)
  return shuffle(seq)
end


# #System Test
#
# def solve_all(grids, name='', showif = 0.0)
#
# end


def solved(values)
  def unitSolved(unit)
    return unit.map{|s| values[s]}.uniq == $digits.uniq
  end
  return values if not false and all($unitList.map{|u| unitSolved(u)})
end


def random_puzzle()
  n = 17
  # values = Hash.new[$squares.map{|s| (s, digits)}]
  values = {}
  $squares.map{|s| values[s] = deep_copy($digits)}
  for s in shuffled($squares)
    break if not assign(values, s, values[s].sample)
    ds = [$squares.map{|s| values[s] if values[s].size == 1}]
    aux = ""
    if ds.size >= n and ds.uniq.size>= 8
      aux.join($squares.map{|s| if values[s].size == 1 then values[s] else "." end})
    end
  end
  return random_puzzle()
end

def deep_copy(obj)
  return Marshal.load(Marshal.dump(obj))
end

# main
grid1  = "003020600900305001001806400008102900700000008006708200002609500800203009005010300"
grid2  = "4.....8.5.3..........7......2.....6.....8.4......1.......6.3.7.5..2.....1.4......"
hard1  = ".....6....59.....82....8....45........3........6..3.54...325..6.................."

# file = ARGV[0]
# grid_str = File.read(file).gsub(/\n/, "")
# display(solve(grid_str))

display(solve(grid2))