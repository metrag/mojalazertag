// PlayerCard.js
import React, { useState, useEffect } from 'react';
import './PlayerCard.css';
import avatar from '../Photo/avatar.png';

const PlayerCard = ({ player, isRed, isFlipped, allFlipped }) => {
  const [isLocalFlipped, setIsLocalFlipped] = useState(false);
  const [formData, setFormData] = useState({
    firstName: '',
    lastName: '',
    group: ''
  });

  useEffect(() => {
    setIsLocalFlipped(isFlipped);
  }, [isFlipped]);

  const handleClick = () => {
    if (!allFlipped) {
      setIsLocalFlipped(!isLocalFlipped);
    }
  };

  const handleInputChange = (e) => {
    const { name, value } = e.target;
    setFormData(prev => ({
      ...prev,
      [name]: value
    }));
  };

  const finalFlipped = allFlipped ? isFlipped : isLocalFlipped;

  const cardStyle = {
    backgroundColor: isRed ? 'rgba(255, 0, 0, 0.3)' : 'rgba(255, 255, 255, 0.1)',
    border: isRed ? '2px solid red' : 'none'
  };

  return (
    <div
      className={`player-card ${finalFlipped ? 'flipped' : ''}`}
      onClick={handleClick}
    >
      <div className="card" style={cardStyle}>
        <div className="front">
          <img src={avatar} alt="Player" className="player-image" />
          <p className="player-name">{formData.lastName || 'Новый игрок'}</p>
        </div>
        <div className="back">
          <div className="player-info">
            <div className="input-group">
              <label>Имя:</label>
              <input
                type="text"
                name="firstName"
                value={formData.firstName}
                onChange={handleInputChange}
                onClick={(e) => e.stopPropagation()}
              />
            </div>
            <div className="input-group">
              <label>Фамилия:</label>
              <input
                type="text"
                name="lastName"
                value={formData.lastName}
                onChange={handleInputChange}
                onClick={(e) => e.stopPropagation()}
              />
            </div>
            <div className="input-group">
              <label>Группа:</label>
              <input
                type="text"
                name="group"
                value={formData.group}
                onChange={handleInputChange}
                onClick={(e) => e.stopPropagation()}
              />
            </div>
          </div>
        </div>
      </div>
    </div>
  );
};

export default PlayerCard;
