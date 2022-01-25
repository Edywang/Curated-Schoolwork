import pygame

pygame.sprite.spritecollide()
# Find sprites in a group that intersect another sprite.
# spritecollide(sprite, group, dokill, collided = None) -> Sprite_list
# sprite parameter = individual sprite
# group parameter = group of sprites
# dokill parameter = boolean, true means take out sprite from group on collision
# collided parameter = callback function that overwrites the check for collision
pygame.sprite.groupcollide()
# groupcollide(group1, group2, dokill1, dokill2, collided = None) -> Sprite_dict
# group1 = first group of sprites
# group2 = second group of sprites
# dokill1 parameter = boolean, true means take out sprite1 from group1 on collision
# dokill2 parameter = boolean, true means take out sprite2 from group2 on collision
pygame.sprite.spritecollideany()
# spritecollideany(sprite, group, collided = None) -> Sprite Collision with the returned sprite.
# spritecollideany(sprite, group, collided = None) -> None No collision
# Working theory of this method is that it checks for any collision with a sprite
# sprite parameter = individual sprite
# group parameter = specifies a group to check for collision against