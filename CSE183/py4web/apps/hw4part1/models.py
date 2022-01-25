"""
This file defines the database models
"""
import datetime

from . common import db, Field, auth
from pydal.validators import *

### Define your table below
#
# db.define_table('thing', Field('name'))
#
## always commit your models to avoid problems later
#
# db.commit()
#

def get_time():
    return datetime.datetime.utcnow()

def get_user_email():
    return auth.current_user.get('email')

db.define_table(
    'person',
    Field('user_email', default=get_user_email),
    Field('first_name', 'string', default=None),
    Field('last_name', 'string', default=None),
)

# We do not want these fields to appear in forms by default.
db.person.id.readable = False
db.person.user_email.readable = False

db.commit()
