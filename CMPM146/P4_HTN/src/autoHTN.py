# python autoHTN.py
import pyhop
import json
from collections import OrderedDict

item_maxes = {}
crafting_recipes = {}
crafting_consumes = {}
crafting_requires = {}

def check_enough (state, ID, item, num):
	if getattr(state,item)[ID] >= num: return []
	# return [('produce', ID, item), ('have_enough', ID, item, num)]
	return False


def produce_enough (state, ID, item, num):
	return [('produce', ID, item), ('have_enough', ID, item, num)]

pyhop.declare_methods ('have_enough', check_enough, produce_enough)
# pyhop.declare_methods ('have_enough', check_enough)

def produce (state, ID, item):
	return [('produce_{}'.format(item), ID)]

pyhop.declare_methods ('produce', produce)


def make_method (name, rule):
	def method (state, ID):
		return_val = [('op_' + name, ID)]
		if not rule.get('Requires') is None:
			for item in rule.get('Requires').keys():
				curr_item_index = 0
				inserted = False
				while 'have_enough' == return_val[curr_item_index][0] and not return_val[curr_item_index][2] in rule.get('Consumes').keys():
					requires_items = return_val[curr_item_index][2] in crafting_requires.keys()
					if requires_items:
						required_items = crafting_requires.get(return_val[curr_item_index][2]).keys()
					if requires_items and item in required_items:
						return_val.insert(curr_item_index, ('have_enough', ID, item, rule['Requires'].get(item)))
						inserted = True
						break
					curr_item_index += 1
				if not inserted:
					return_val.insert(curr_item_index, ('have_enough', ID, item, rule['Requires'].get(item)))
		if not rule.get('Consumes') is None:
			for item in rule.get('Consumes').keys():
				curr_item_index = 0
				inserted = False
				# print(return_val[curr_item_index][0])
				# quit()
				while 'have_enough' == return_val[curr_item_index][0]:
					print("ITEM TO CHECK", return_val[curr_item_index][2])
					# print(item)
					# print(crafting_consumes.get(item))
					# quit()
					consumes_items = return_val[curr_item_index][2] in crafting_consumes.keys()
					print("ITEM IN crafting_consumes", consumes_items)
					if consumes_items:
						consumed_items = crafting_consumes.get(return_val[curr_item_index][2]).keys()
					requires_items = return_val[curr_item_index][2] in crafting_requires.keys() and not crafting_requires.get(return_val[curr_item_index][2]) is None
					if requires_items:
						required_items = crafting_requires.get(return_val[curr_item_index][2]).keys()
					if consumes_items and item in consumed_items:
						return_val.insert(curr_item_index, ('have_enough', ID, item, rule['Consumes'].get(item)))
						inserted = True
						break
					if requires_items and item in required_items:
						return_val.insert(curr_item_index, ('have_enough', ID, item, rule['Consumes'].get(item)))
						inserted = True
						break
					# if not return_val[curr_item_index][2] in crafting_consumes.keys() or item in crafting_consumes.get(return_val[curr_item_index][2]) or item in crafting_requires.get(return_val[curr_item_index][2]):
					curr_item_index += 1
				if not inserted:
					return_val.insert(-2, ('have_enough', ID, item, rule['Consumes'].get(item)))
		return return_val
	method.__name__ = name
	return method


def declare_methods (data):
	# some recipes are faster than others for the same product even though they might require extra tools
	# sort the recipes so that faster recipes go first

	# your code here
	# sort the json on input
	created_methods = []
	for key, recipe in sorted(data['Recipes'].items(), key=lambda item: item[1]["Time"], reverse=False):
		result_item = list(data['Recipes'].get(key).get('Produces').keys())[0]
		method_name = "produce_" + result_item
		if result_item not in created_methods:
			method_list = []
			for key1, _ in sorted(data['Recipes'].items(), key=lambda item: item[1]["Time"], reverse=False):
				if list(data['Recipes'].get(key1).get('Produces').keys())[0] == result_item:
					method_list.append(make_method(key1.replace(" ", "_"), data['Recipes'].get(key1)))
		pyhop.declare_methods(method_name, *method_list)
		created_methods.append(result_item)


def make_operator (name, rule):
	def operator (state, ID):
		if not rule.get('Consumes') is None:
			for item in rule['Consumes'].keys():
				if not getattr(state, item)[ID] >= rule['Consumes'].get(item):
					return False
		if not rule.get('Requires') is None:
			for item in rule['Requires'].keys():
				if not getattr(state, item)[ID] >= rule['Requires'].get(item):
					return False
		if not rule.get('Consumes') is None:
			for item in rule['Consumes'].keys():
				setattr(state, item, {ID: getattr(state, item)[ID] - rule['Consumes'].get(item)})
		for item in rule['Produces']:
			setattr(state, item, {ID: getattr(state, item)[ID] + rule['Produces'].get(item)})
		state.time[ID] -= rule['Time']
		return state
	operator.__name__ = "op_" + name.replace(" ", "_")
	return operator


def declare_operators (data):
	# your code here
	# hint: call make_operator, then declare the operator to pyhop using pyhop.declare_operators(o1, o2, ..., ok)
	for key in data['Recipes'].keys():
		pyhop.declare_operators(make_operator(key, data['Recipes'].get(key)))


def add_heuristic (data, ID):
	# prune search branch if heuristic() returns True
	# do not change parameters to heuristic(), but can add more heuristic functions with the same parameters: 
	# e.g. def heuristic2(...); pyhop.add_check(heuristic2)
	depth_visits = {}
	def depth_visited_too_much (state, curr_task, tasks, plan, depth, calling_stack):
		if depth_visits.get(depth) is None:
			depth_visits.update({depth: 0})
		else:
			depth_visits.update({depth + 1: depth_visits.get(depth + 1) + 1})
			depth_visits.update({depth: depth_visits.get(depth) - 1})
		return depth_visits.get(depth) > 1

	def too_much_of_item (state, curr_task, tasks, plan, depth, calling_stack):
		for item_name in item_maxes.keys():
			if getattr(state, item_name)[ID] > item_maxes.get(item_name):
				return True
		return False
		
		
	def no_time (state, curr_task, tasks, plan, depth, calling_stack):
		if state.time[ID] < 0:
			return True
		return False # if True, prune this branch
	
	# pyhop.add_check(bad_plan)
	# pyhop.add_check(depth_visited_too_much)
	pyhop.add_check(too_much_of_item)
	pyhop.add_check(no_time)


def set_up_state (data, ID, time=0):
	state = pyhop.State('state')
	state.time = {ID: time}

	for item in data['Items']:
		setattr(state, item, {ID: 0})
		# item_maxes[item] = 0
		# setattr(state, item_maxes, {ID: 0})

	for item in data['Tools']:
		setattr(state, item, {ID: 0})
		item_maxes.update({item: 1})
		# setattr(state, item + " max", {ID: 1})

	for item, num in data['Initial'].items():
		setattr(state, item, {ID: num})
		if item_maxes.get(item) is not None and num > item_maxes.get(item):
			item_maxes.update({item: num})
		# if num > getattr(state, item + " max"):
		# 	setattr(state, item + " max", {ID: num})

	# for recipe in data['Recipes'].values():
	# 	if not recipe.get('Consumes') is None:
	# 		for item in recipe.get('Consumes').keys():
	# 			if recipe.get('Consumes').get(item) > item_maxes[item]:
	# 				item_maxes[item] = recipe.get('Consumes').get(item)
	return state

def set_up_goals (data, ID):
	goals = []
	for item, num in data['Goal'].items():
		goals.append(('have_enough', ID, item, num))
		# if item_maxes.get(item) is None or num > item_maxes[item]:
		# 	item_maxes.update({item: num})
	
	return goals

def round_up(num1, num2):
	temp_num = num2
	while temp_num < num1:
		temp_num += num2
	return temp_num

if __name__ == '__main__':
	rules_filename = 'crafting.json'

	with open(rules_filename) as f:
		data = json.load(f)

	state = set_up_state(data, 'agent', time=100) # allot time here
	goals = set_up_goals(data, 'agent')

	for recipe_name, recipe in data.get("Recipes").items():
		if "craft" in recipe_name:
			recipe_name_split = recipe_name.split(" ")
			crafting_recipes.update({recipe_name_split[recipe_name.index("craft") + 1]: recipe})
		elif "smelt" in recipe_name:
			recipe_name_split = recipe_name.split(" ")
			crafting_recipes.update({list(recipe.get("Produces").keys())[0]: recipe})

	for recipe_name, recipe in crafting_recipes.items():
		crafting_consumes.update({recipe_name: recipe.get("Consumes")})
		crafting_requires.update({recipe_name: recipe.get("Requires")})
	# for recipe in data['Recipes'].values():
	# 	for item in recipe.get('Produces').keys():
	# 		if item_maxes.get(item) is not None and item_maxes[item] % recipe.get('Produces').get(item) != 0:
	# 			item_maxes[item] = round_up(item_maxes[item] , recipe.get('Produces').get(item))
	# print("ITEM_MAXES:", item_maxes)

	declare_operators(data)
	declare_methods(data)
	add_heuristic(data, 'agent')

	# pyhop.print_operators()
	# pyhop.print_methods()
	# quit()

	# Hint: verbose output can take a long time even if the solution is correct; 
	# try verbose=1 if it is taking too long
	pyhop.pyhop(state, goals, verbose=3)
	# pyhop.pyhop(state, [('have_enough', 'agent', 'cart', 1),('have_enough', 'agent', 'rail', 20)], verbose=3)
